/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmdsp_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:05:31 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/26 19:00:00 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	ex_all_close(t_cmds *cmdsp, char **envp)
{
	t_cmds	*tmp;
	int		i;

	i = 0;
	if (envp != NULL)
	{
		while (envp[i] != NULL)
			free(envp[i++]);
		free(envp);
	}
	tmp = cmdsp;
	cmdsp = cmdsp->next;
	free(tmp);
	while (cmdsp != NULL)
	{
		vec_free(&(cmdsp->argv));
		tmp = cmdsp;
		cmdsp = cmdsp->next;
		free(tmp);
	}
}

t_cmds	*ex_cmdsp_init(int *eno)
{
	t_cmds	*cmdsp_head;

	cmdsp_head = ft_calloc_s(sizeof(t_cmds), 1);
	cmdsp_head->enop = eno;
	return (cmdsp_head);
}

t_cmds	*ex_cmdsp_add_back(t_cmds *cmdsp, int *eno)
{
	t_cmds	*new;
	t_cmds	*node;

	new = ft_calloc_s(sizeof(t_cmds), 1);
	node = cmdsp;
	while (node->next != NULL)
		node = node->next;
	node->next = new;
	new->enop = eno;
	return (new);
}
