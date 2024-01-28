/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mktr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:14:26 by michang           #+#    #+#             */
/*   Updated: 2024/01/25 14:43:15 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mktr_print_unexpected(char *str, int *eno)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'\n", 2);
	*eno = 258;
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
