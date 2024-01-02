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

t_tr_node	*mktr_word(t_token **tk_now)
{

}

t_tr_node	*mktr_redir(t_token **tk_now)
{

}

t_tr_node	*mktr_command_part(t_token **tk_now)
{

}

t_tr_node	*mktr_command(t_token **tk_now)
{

}

t_tr_node	*mktr_pipeline(t_token **tk_now)
{
	t_tr_node	*node;

	node = mktr_alloc_s(TR_PIPELINE, 0);
	if (!(*tk_now) && (*tk_now)->type == T_PARENT_L)
	{
		
	}
	else
	{

	}
}

t_tr_node	*mktr_list(t_token **tk_now)
{
	t_tr_node	*node;

	if (!(*tk_now))
		return (0);
	node = mktr_alloc_s(TR_LIST, 0);
	node->left = mktr_pipeline(tk_now);
	if (!(*tk_now) && ((*tk_now)->type == T_AND || (*tk_now)->type == T_OR))
	{
		node->tk = *tk_now;
		*tk_now = (*tk_now)->next;
		node->left = mktr_list(tk_now);
	}
	return (node);
}

void	mktr_make_tree(t_token *tk_head)
{
	t_tr_node	*root;
	t_token		*tk_now;
	
	tk_now = tk_head;
	root = mktr_list(&tk_now);
}
