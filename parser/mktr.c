/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mktr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:14:26 by michang           #+#    #+#             */
/*   Updated: 2024/01/01 20:14:27 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
int	mktr_command_part(t_tr_node **head, t_token **tk_now)
{
	if (!((*tk_now)->type >= T_REDIR_S_L && (*tk_now)->type <= T_REDIR_D_R)
		&& (*tk_now)->type != T_WORD)
		return (1);
	*head = mktr_alloc_s(TR_COMMAND_PART, 0);
	(*head)->tk = *tk_now;
	if ((*tk_now)->type >= T_REDIR_S_L && (*tk_now)->type <= T_REDIR_D_R)
	{
		*tk_now = (*tk_now)->next;
		if ((*tk_now)->type != T_WORD)
			return (1);
		else
			(*head)->tk->str = (*tk_now)->str;
	}
	*tk_now = (*tk_now)->next;
	return (0);
}

//<command>			::= <command_part> {<command_part>}
int	mktr_command(t_tr_node **head, t_token **tk_now)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_COMMAND, 0);
	if (mktr_command_part(&((*head)->left), tk_now))
		return (1);
	while (*tk_now && ((*tk_now)->type == T_WORD \
		|| ((*tk_now)->type >= T_REDIR_S_L && (*tk_now)->type <= T_REDIR_D_R)))
	{
		next_node = mktr_alloc_s(TR_COMMAND, 0);
		next_node->left = *head;
		if (mktr_command_part(&(next_node->right), tk_now))
			return (1);
		*head = next_node;
	}
	return (0);
}

//<pipeline>		::= "(" <list> ")"
// 					| <command> {"|" <command>}
int	mktr_pipeline(t_tr_node **head, t_token **tk_now)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_PIPELINE, 0);
	if (*tk_now && (*tk_now)->type == T_PARENT_L)
	{
		*tk_now = (*tk_now)->next;
		if (mktr_list(&((*head)->left), tk_now))
			return (1);
		if (*tk_now && (*tk_now)->type != T_PARENT_R)
			return (1);
		*tk_now = (*tk_now)->next;
		return (0);
	}
	if (mktr_command(&((*head)->left), tk_now))
		return (1);
	while (*tk_now && (*tk_now)->type == T_PIPE)
	{
		*tk_now = (*tk_now)->next;
		next_node = mktr_alloc_s(TR_PIPELINE, 0);
		next_node->left = *head;
		if (mktr_command(&(next_node->right), tk_now))
			return (1);
		*head = next_node;
	}
	return (0);
}

// <list>			::= <pipeline> {("&&" | "||") <pipeline>}
int	mktr_list(t_tr_node **head, t_token **tk_now)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_LIST, 0);
	if (mktr_pipeline(&((*head)->left), tk_now))
		return (1);
	while (*tk_now && ((*tk_now)->type == T_AND || (*tk_now)->type == T_OR))
	{
		(*head)->tk = *tk_now;
		*tk_now = (*tk_now)->next;
		next_node = mktr_alloc_s(TR_LIST, 0);
		next_node->left = *head;
		if (mktr_pipeline(&(next_node->right), tk_now))
			return (1);
		*head = next_node;
	}
	return (0);
}

int	mktr_make_tree(t_token *tk_head, t_tr_node **root)
{
	t_token		*tk_now;

	tk_now = tk_head;
	if (mktr_list(root, &tk_now) || tk_now->type != T_NEWLINE)
		return (mktr_print_unexpected(tk_now->str));
	else
		return (0);
		// return (test_tr_print_tree(*root, "INIT TREE"));
}