/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:37:45 by michang           #+#    #+#             */
/*   Updated: 2024/01/04 20:37:46 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	trtv_env_expand(t_tr_node *node)
{
	if (!node)
		return ;
	test_print_node(node);
	trtv_env_expand(node->left);
	trtv_env_expand(node->right);
}

void	trtv_traversal(t_tr_node *root)
{
	trtv_env_expand(root);
}
