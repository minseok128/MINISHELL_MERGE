/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmdsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:05:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/10 17:34:14 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*ex_make_cmdsp(void)
{
	t_cmds	*cmdsp_head;

	cmdsp_head = ft_calloc_s(sizeof(t_cmds), 1);
	if (cmdsp_head == NULL)
		exit(0);
	return (cmdsp_head);
}

void	ex_add_cmdsp_node(t_cmds *cmdsp, char **argv, char *in, char *out)
{
	t_cmds	*new;
	t_cmds	*node;

	new = ft_calloc_s(sizeof(t_cmds), 1);
	if (new == NULL)
		exit(0);
	new->argv = argv;
	new->in_file = in;
	new->out_file = out;
	node = cmdsp;
	while(node->next != NULL)
		node = node->next;
	node->next = new;
}