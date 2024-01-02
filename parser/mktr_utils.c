/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mktr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:14:26 by michang           #+#    #+#             */
/*   Updated: 2024/01/01 20:14:27 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tr_node	*mktr_alloc_s(t_tr_type bnf_type, t_token *tk)
{
	t_tr_node	*node;

	node = ft_calloc_s(1, sizeof(t_tr_node));
	node->bnf_type = bnf_type;
	if (tk)
		node->tk = tk;
	return (node);
}