/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mktr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:14:26 by michang           #+#    #+#             */
/*   Updated: 2024/01/18 17:26:54 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

/*
EBNF(by michang)
	<list>			::= <pipeline> {("&&" | "||") <pipeline>}

	<pipeline>		::= "(" <list> ")"
					| <command> {"|" <command>}

	<command>		::= <command_part> {<command_part>}

	<command_part>	::= (">" | ">>" | "<" | "<<") <word>
					| <word>
*/

// <command_part>	::= <word>
//					| <redir>
int	mktr_command_part(t_tr_node **head, t_token **tk_now, t_mktr_info *info)
{
	if (!((*tk_now)->type >= T_REDIR_S_L && (*tk_now)->type <= T_REDIR_D_R)
		&& (*tk_now)->type != T_WORD)
		return (1);
	*head = mktr_alloc_s(TR_COMMAND_PART, *tk_now);
	if ((*tk_now)->type >= T_REDIR_S_L && (*tk_now)->type <= T_REDIR_D_R)
	{
		if ((*tk_now)->next->type != T_WORD)
		{
			*tk_now = (*tk_now)->next;
			return (1);
		}
		if ((*tk_now)->type == T_REDIR_D_L)
		{
			info->is_hdoc_signal = mktr_heredoc(&((*tk_now)->next->str));
			vec_push_back(&(info->hdocs), (*tk_now)->next->str);
			if (info->is_hdoc_signal == 1)
				return (1);
		}
		*tk_now = (*tk_now)->next;
		free((*head)->tk->str);
		(*head)->tk->str = (*tk_now)->str;
		(*tk_now)->str = 0;
	}
	*tk_now = (*tk_now)->next;
	return (0);
}

//<command>			::= <command_part> {<command_part>}
int	mktr_command(t_tr_node **head, t_token **tk_now, t_mktr_info *info)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_COMMAND, 0);
	if (mktr_command_part(&((*head)->left), tk_now, info))
		return (1);
	while (*tk_now && ((*tk_now)->type == T_WORD \
		|| ((*tk_now)->type >= T_REDIR_S_L && (*tk_now)->type <= T_REDIR_D_R)))
	{
		next_node = mktr_alloc_s(TR_COMMAND, 0);
		next_node->left = *head;
		*head = next_node;
		if (mktr_command_part(&(next_node->right), tk_now, info))
			return (1);
	}
	return (0);
}

//<pipeline>		::= "(" <list> ")"
// 					| <command> {"|" <command>}
int	mktr_pipeline(t_tr_node **head, t_token **tk_now, t_mktr_info *info)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_PIPELINE, 0);
	if (*tk_now && (*tk_now)->type == T_PARENT_L)
	{
		*tk_now = (*tk_now)->next;
		if (mktr_list(&((*head)->left), tk_now, info))
			return (1);
		if (*tk_now && (*tk_now)->type != T_PARENT_R)
			return (1);
		*tk_now = (*tk_now)->next;
		return (0);
	}
	if (mktr_command(&((*head)->left), tk_now, info))
		return (1);
	while (*tk_now && (*tk_now)->type == T_PIPE)
	{
		*tk_now = (*tk_now)->next;
		next_node = mktr_alloc_s(TR_PIPELINE, 0);
		next_node->left = *head;
		*head = next_node;
		if (mktr_command(&(next_node->right), tk_now, info))
			return (1);
	}
	return (0);
}

// <list>			::= <pipeline> {("&&" | "||") <pipeline>}
int	mktr_list(t_tr_node **head, t_token **tk_now, t_mktr_info *info)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_LIST, 0);
	if (mktr_pipeline(&((*head)->left), tk_now, info))
		return (1);
	while (*tk_now && ((*tk_now)->type == T_AND || (*tk_now)->type == T_OR))
	{
		(*head)->tk = *tk_now;
		*tk_now = (*tk_now)->next;
		next_node = mktr_alloc_s(TR_LIST, 0);
		next_node->left = *head;
		*head = next_node;
		if (mktr_pipeline(&(next_node->right), tk_now, info))
			return (1);
	}
	return (0);
}

int	mktr_make_tree(t_token *tk_head, t_tr_node **root)
{
	int			i;
	t_token		*tk_now;
	t_mktr_info	info;

	info.is_hdoc_signal = 0;
	vec_init(&(info.hdocs), 1);
	tk_now = tk_head;
	if (mktr_list(root, &tk_now, &info))
	{
		if (info.is_hdoc_signal == 1)
		{
			i = 0;
			while (i < info.hdocs.size)
				unlink(info.hdocs.items[i++]);
			vec_free(&(info.hdocs));
			return (1);
		}
		vec_free(&(info.hdocs));
		return (mktr_print_unexpected(tk_now->str));
	}
	vec_free(&(info.hdocs));
	if (tk_now->type != T_NEWLINE)
		return (mktr_print_unexpected(tk_now->str));
	return (0);
}
