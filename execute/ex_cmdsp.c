/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmdsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:05:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/17 15:36:57 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*ex_cmdsp_init(void)
{
	t_cmds	*cmdsp_head;

	cmdsp_head = ft_calloc_s(sizeof(t_cmds), 1);
	if (cmdsp_head == NULL)
		exit(0);
	return (cmdsp_head);
}

t_cmds	*ex_cmdsp_add_back(t_cmds *cmdsp)
{
	t_cmds	*new;
	t_cmds	*node;

	new = ft_calloc_s(sizeof(t_cmds), 1);
	if (new == NULL)
		exit(0);
	node = cmdsp;
	while (node->next != NULL)
		node = node->next;
	node->next = new;
	return (new);
}