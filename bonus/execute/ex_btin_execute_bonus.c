/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_btin_execute_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:08:04 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/26 20:03:40 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	ex_btin_redir_on(t_cmds *cmds, int *fd)
{
	if ((cmds->type & RD_AMBIGUOUS) != 0)
	{
		btin_out(0, 1, btin_make_errmsg("minishell", \
			"\0", "ambiguous redirect"), cmds->enop);
		return (1);
	}
	if (cmds->in_file != NULL)
		fd[0] = ex_open_btin_input_fd(cmds);
	if (fd[0] == -1)
		return (1);
	if (cmds->out_file != NULL)
		fd[1] = ex_open_btin_output_fd(cmds);
	return (0);
}

int	ex_exec_btin(t_cmds *cmds, t_envs *envsp, int fork_flag)
{	
	if (!cmds->argv.items[0])
		return (1);
	else if (ft_strncmp(cmds->argv.items[0], "cd", 3) == 0)
		btin_cd(cmds, envsp, fork_flag);
	else if (ft_strncmp(cmds->argv.items[0], "pwd", 4) == 0)
		btin_pwd(cmds, fork_flag);
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

void	ex_btin_redir_off(t_cmds *cmds, int *fd)
{
	if (fd[0] != -1 && fd[0] != 0)
	{
		close(0);
		ex_dup_to(cmds, fd[0], 0);
		close(fd[0]);
	}
	if (fd[1] != -1 && fd[1] != 1)
	{
		close(1);
		ex_dup_to(cmds, fd[1], 1);
		close(fd[1]);
	}
}

int	ex_is_builtin(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	int	fd[2];

	fd[0] = 0;
	fd[1] = 1;
	if (fork_flag == 0 && ex_btin_redir_on(cmds, fd))
		return (1);
	if (fd[0] == -1 || fd[1] == -1)
	{
		ex_btin_redir_off(cmds, fd);
		return (1);
	}
	if (ex_exec_btin(cmds, envsp, fork_flag) == 0)
	{
		if (fork_flag == 1)
			return (0);
		else
			ex_btin_redir_off(cmds, fd);
		return (0);
	}
	if (fork_flag == 0)
		ex_btin_redir_off(cmds, fd);
	return (1);
}
