/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:31:16 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 17:30:46 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_is_builtin(t_cmds *cmd, t_envs *envsp)
{
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		builtin_cd(cmd, envsp);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		builtin_export(cmd, envsp);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		builtin_unset(cmd, envsp);
	else if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		builtin_env(envsp);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		builtin_error();
	else
		return (0);
	return (1);
}

char	**ex_change_to_envp(t_envs *envsp)
{
	t_envs	*node;
	char	**envp;
	int		size;
	int		i;

	size = 0;
	node = envsp->next;
	while (node->next != NULL)
	{
		node = node->next;
		size++;
	}
	envp = malloc(sizeof(char *) * (size + 1));
	node = envsp->next;
	i = 0;
	while (i < size)
		envp[i++] = ft__strjoin(node->key, node->value);
	envp[i] = NULL;
	return (envp);
}

int	ex_process_command(t_cmds *cmdsp_head, t_envs *envsp)
{
	t_cmds	*cmdsp;
	char	**envp;
	int		status;
	pid_t	pid;

	cmdsp = cmdsp_head->next;
	//단일 builtin 명령어 처리
	if (cmdsp->next == NULL && ex_is_builtin(cmdsp, envsp) == 1)
		;
	else
	{
		envp = ex_change_to_envp(envsp);
		while (cmdsp->next != NULL)
		{
			pid = ex_do_pipe();
			cmdsp = cmdsp->next;
		}
		waitpid(pid, &status, NULL);
		while (waitpid(-1, NULL, NULL) != -1)
			;
		if (status & 127 != 0)
			return ((status >> 8) + 128);
		else
			return (status >> 8);
	}
	return (0);
}