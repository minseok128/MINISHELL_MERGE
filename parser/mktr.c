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
int	mktr_command_part(t_tr_node **head, t_vector *tks, int *now)
{
	if (!(tks->items[*now] >= T_REDIR_S_L && tks->items[*now] <= T_REDIR_D_R)
		&& tks->items[*now] != T_WORD)
		return (1);
	*head = mktr_alloc_s(TR_COMMAND_PART, 0);
	(*head)->tk = tks->items[*now];
	if (tks->items[*now] >= T_REDIR_S_L && tks->items[*now] <= T_REDIR_D_R)
	{
		*now += 1;
		if (tks->items[*now] != T_WORD)
			return (1);
		else
			(*head)->tk->str = ((t_token *)(tks->items[*now]))->str;
	}
	*now += 1;
	return (0);
}

//<command>			::= <command_part> {<command_part>}
int	mktr_command(t_tr_node **head, t_vector *tks, int *now)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_COMMAND, 0);
	if (mktr_command_part(&((*head)->left), tks, now))
		return (1);
	while (*now < tks->size && (tks->items[*now] == T_WORD \
		|| (tks->items[*now] >= T_REDIR_S_L && tks->items[*now] <= T_REDIR_D_R)))
	{
		next_node = mktr_alloc_s(TR_COMMAND, 0);
		next_node->left = *head;
		if (mktr_command_part(&(next_node->right), tks, now))
			return (1);
		*head = next_node;
	}
	return (0);
}

//<pipeline>		::= "(" <list> ")"
// 					| <command> {"|" <command>}
int	mktr_pipeline(t_tr_node **head, t_vector *tks, int *now)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_PIPELINE, 0);
	if (*now < tks->size && tks->items[*now] == T_PARENT_L)
	{
		*now += 1;
		if (mktr_list(&((*head)->left), tks, now))
			return (1);
		if (*now < tks->size && tks->items[*now] != T_PARENT_R)
			return (1);
		*now += 1;
		return (0);
	}
	if (mktr_command(&((*head)->left), tks, now))
		return (1);
	while (*now < tks->size && tks->items[*now] == T_PIPE)
	{
		*now += 1;
		next_node = mktr_alloc_s(TR_PIPELINE, 0);
		next_node->left = *head;
		if (mktr_command(&(next_node->right), tks, now))
			return (1);
		*head = next_node;
	}
	return (0);
}

// <list>			::= <pipeline> {("&&" | "||") <pipeline>}
int	mktr_list(t_tr_node **head, t_vector *tks, int *now)
{
	t_tr_node	*next_node;

	*head = mktr_alloc_s(TR_LIST, 0);
	if (mktr_pipeline(&((*head)->left), tks, now))
		return (1);
	while (*now < tks->size
		&& (tks->items[*now] == T_AND || tks->items[*now] == T_OR))
	{
		(*head)->tk = tks->items[*now];
		*now += 1;
		next_node = mktr_alloc_s(TR_LIST, 0);
		next_node->left = *head;
		if (mktr_pipeline(&(next_node->right), tks, now))
			return (1);
		*head = next_node;
	}
	return (0);
}

int	mktr_make_tree(t_vector *tks, t_tr_node **root)
{
	int	now;

	now = 0;
	if (mktr_list(root, tks, &now) || tks->items[now] != T_NEWLINE)
		return (mktr_print_unexpected(tks->items[now]);
	else
		return (test_tr_print_tree(*root, "INIT TREE"));
}
