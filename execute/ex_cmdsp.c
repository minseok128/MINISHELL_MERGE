/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmdsp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:05:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/10 17:05:55 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

t_cmds	*ex_make_cmdsp(void)
{
	t_cmds	*cmdsp_head;

	cmdsp_head = malloc(sizeof(t_cmds));
	if (cmdsp_head == NULL)
		exit(0);
	cmdsp_head->next = NULL;
	return (cmdsp_head);
}

void	ex_add_cmdsp_node(t_cmds *cmdsp, char **argv, char *in, char *out)
{
	t_cmds	*new;
	t_cmds	*node;

	new = malloc(sizeof(t_cmds));
	if (new == NULL)
		exit(0);
	new->argv = argv;
	new->in_file = in;
	new->out_file = out;
	new->next = NULL;
	node = cmdsp;
	while(node->next != NULL)
		node = node->next;
	node->next = new;
}