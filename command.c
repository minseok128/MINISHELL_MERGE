/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:31:16 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/05 14:52:15 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ex_merge_key_and_value(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	if (str == 0)
		btin_error();
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = '=';
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

int	ex_is_builtin(t_cmds *cmds, t_envs *envsp)
{
	if (ft_strncmp(cmds->argv[0], "cd", 3) == 0)
		btin_cd(cmds, envsp, 0);
	else if (ft_strncmp(cmds->argv[0], "pwd", 4) == 0)
		btin_pwd(0);
	else if (ft_strncmp(cmds->argv[0], "export", 7) == 0)
		btin_export(cmds, envsp, 0);
	else if (ft_strncmp(cmds->argv[0], "unset", 6) == 0)
		btin_unset(cmds, envsp, 0);
	else if (ft_strncmp(cmds->argv[0], "echo", 5) == 0)
		btin_echo(cmds, 0);
	else if (ft_strncmp(cmds->argv[0], "env", 4) == 0)
		btin_env(envsp, 0);
	else if (ft_strncmp(cmds->argv[0], "exit", 5) == 0)
		btin_exit(cmds, 0);
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
		envp[i++] = ex_merge_key_and_value(node->key, node->value);
	envp[i] = NULL;
	return (envp);
}

// int	ex_do_pipe()
// {
	
// }
int	ex_process_command(t_cmds *cmdsp_head, t_envs *envsp)
{
	t_cmds	*cmdsp;
	// char	**envp;
	// int		status;
	// pid_t	pid;

	cmdsp = cmdsp_head->next;
	//단일 builtin 명령어 처리
	if (cmdsp->next == NULL && ex_is_builtin(cmdsp, envsp) == 1)
		;
	// else
	// {
	// 	envp = ex_change_to_envp(envsp);
	// 	while (cmdsp->next != NULL)
	// 	{
	// 		pid = ex_do_pipe(cmdsp);
	// 		cmdsp = cmdsp->next;
	// 	}
	// 	waitpid(pid, &status, NULL);
	// 	while (waitpid(-1, NULL, NULL) != -1)
	// 		;
	// 	if (status & 127 != 0)
	// 		return ((status >> 8) + 128);
	// 	else
	// 		return (status >> 8);
	// }
	return (0);
}