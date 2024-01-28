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

#include "../minishell_bonus.h"

void	btin_free_envsp(t_envs *envsp)
{
	t_envs	*node;

	while (envsp)
	{
		node = envsp;
		free(node->key);
		if (node->value)
			free(node->value);
		envsp = envsp->next;
		free(node);
	}
}

void	btin_env(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	t_envs	*node;

	node = envsp->next;
	while (node != NULL)
	{
		if (node->value != NULL)
		{
			ft_putstr_fd(node->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(node->value, 1);
			ft_putchar_fd('\n', 1);
		}
		node = node->next;
	}
	btin_out(fork_flag, 0, NULL, cmds->enop);
}
