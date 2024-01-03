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

#include "parser.h"

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
t_tr_node	*mktr_command_part(t_token **tk_now, int *is_error)
{
	t_tr_node	*node;

	if (!(*tk_now))
		return (0);
	node = mktr_alloc_s(TR_COMMAND_PART, 0);
	node->tk = *tk_now;
	if ((*tk_now)->type >= T_REDIR_S_L && (*tk_now)->type <= T_REDIR_D_R)
	{
		*tk_now = (*tk_now)->next;
		if ((*tk_now)->type != T_WORD)
			*is_error = 1;
		else
			node->tk->str = (*tk_now)->str;
	}
	*tk_now = (*tk_now)->next;
	return (node);
}

//<command>			::= <command_part> {<command_part>}
t_tr_node	*mktr_command(t_token **tk_now, int *is_error)
{
	t_tr_node	*node;
	t_tr_node	*next_node;

	node = mktr_alloc_s(TR_COMMAND, 0);
	node->left = mktr_command_part(tk_now, is_error);
	while (*tk_now && ((*tk_now)->type == T_WORD \
		|| ((*tk_now)->type >= T_REDIR_S_L && (*tk_now)->type <= T_REDIR_D_R)))
	{
		next_node = mktr_alloc_s(TR_COMMAND, 0);
		next_node->left = node;
		next_node->right = mktr_command_part(tk_now, is_error);
		node = next_node;
	}
	return (node);
}

//<pipeline>		::= "(" <list> ")"
// 					| <command> {"|" <command>}
t_tr_node	*mktr_pipeline(t_token **tk_now, int *is_error)
{
	t_tr_node	*node;
	t_tr_node	*next_node;

	node = mktr_alloc_s(TR_PIPELINE, 0);
	if (*tk_now && (*tk_now)->type == T_PARENT_L)
	{
		*tk_now = (*tk_now)->next;
		node->left = mktr_list(tk_now, is_error);
		if (*tk_now && (*tk_now)->type == T_PARENT_R)
			*tk_now = (*tk_now)->next;
		else
			*is_error = 1;
		return (node);
	}
	node->left = mktr_command(tk_now, is_error);
	while (*tk_now && (*tk_now)->type == T_PIPE)
	{
		*tk_now = (*tk_now)->next;
		next_node = mktr_alloc_s(TR_PIPELINE, 0);
		next_node->left = node;
		next_node->right = mktr_command(tk_now, is_error);
		node = next_node;
	}
	return (node);
}

// <list>			::= <pipeline> {("&&" | "||") <pipeline>}
t_tr_node	*mktr_list(t_token **tk_now, int *is_error)
{
	t_tr_node	*node;
	t_tr_node	*next_node;

	node = mktr_alloc_s(TR_LIST, 0);
	node->left = mktr_pipeline(tk_now, is_error);
	while (*tk_now && ((*tk_now)->type == T_AND || (*tk_now)->type == T_OR))
	{
		node->tk = *tk_now;
		*tk_now = (*tk_now)->next;
		next_node = mktr_alloc_s(TR_LIST, 0);
		next_node->left = node;
		next_node->right = mktr_pipeline(tk_now, is_error);
		node = next_node;
	}
	return (node);
}

void	mktr_make_tree(t_token *tk_head)
{
	t_tr_node	*root;
	t_token		*tk_now;
	int			is_error;

	is_error = 0;
	tk_now = tk_head;
	root = mktr_list(&tk_now, &is_error);
	printf("[TREE] DONE! <tk:%s, bnf:%d>\n│\n", tk_now ? tk_now->str : 0, root->bnf_type);
	test_tr_print_tree(root);
}
