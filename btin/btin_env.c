/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:10 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:26:29 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	btin_env(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	int		out_fd;
	t_envs	*node;

	if (envsp == NULL)
		return ;
	out_fd = btin_out_fd(cmds, fork_flag);
	if (out_fd == -1)
		return ;
	node = envsp->next;
	while (node != NULL)
	{
		if (node->value != NULL)
		{
			ft_putstr_fd(node->key, out_fd);
			ft_putchar_fd('=', out_fd);
			ft_putstr_fd(node->value, out_fd);
			ft_putchar_fd('\n', out_fd);
		}
		node = node->next;
	}
	if (out_fd != 1)
		close(out_fd);
	btin_out(fork_flag, 0, NULL);
}
