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

#include "../minishell.h"

int	mktr_print_unexpected(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (1);
}

int	mktr_free_node(t_tr_node *node)
{
	free(node);
	return (1);
}

t_tr_node	*mktr_alloc_s(t_tr_type bnf_type, t_token *tk)
{
	t_tr_node	*node;

	node = ft_calloc_s(1, sizeof(t_tr_node));
	node->bnf_type = bnf_type;
	if (tk)
		node->tk = tk;
	return (node);
}
