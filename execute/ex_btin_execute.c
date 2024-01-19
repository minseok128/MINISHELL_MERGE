/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_btin_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:08:04 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/19 15:08:24 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ex_is_builtin(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	if (ft_strncmp(cmds->argv.items[0], "cd", 3) == 0)
		btin_cd(cmds, envsp, fork_flag);
	else if (ft_strncmp(cmds->argv.items[0], "pwd", 4) == 0)
		btin_pwd(fork_flag);
	else if (ft_strncmp(cmds->argv.items[0], "export", 7) == 0)
		btin_export(cmds, envsp, 0, fork_flag);
	else if (ft_strncmp(cmds->argv.items[0], "unset", 6) == 0)
		btin_unset(cmds, envsp, fork_flag);
	else if (ft_strncmp(cmds->argv.items[0], "echo", 5) == 0)
		btin_echo(cmds, fork_flag);
	else if (ft_strncmp(cmds->argv.items[0], "env", 4) == 0)
		btin_env(envsp, fork_flag);
	else if (ft_strncmp(cmds->argv.items[0], "exit", 5) == 0)
		btin_exit(cmds, fork_flag);
	else
		return (0);
	return (1);
}