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

void	mktr_word(t_token *tk, t_tr_node **node)
{

}

void	mktr_redir(t_token *tk, t_tr_node **node)
{

}

void	mktr_command_part(t_token *tk, t_tr_node **node)
{

}

void	mktr_command(t_token *tk, t_tr_node **node)
{

}

void	mktr_pipeline(t_token *tk, t_tr_node **node)
{

}

void	mktr_list(t_token *tk, t_tr_node **node)
{
	t_tr_node	*left;
	t_tr_node	*right;

	mktr_pipeline(tk, node);
}

void	mktr_make_tree(t_token *tk_head)
{
	t_tr_node	*root;


}
