/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:12:59 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/10 17:14:37 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	*ex_free_string_array(char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i] != NULL)
	{
		free(string_array[i]);
		i++;
	}
	return (NULL);
}

char	*ex_strjoin_c(char const *s1, char const *s2, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = ft_calloc_s(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

int	ex_is_builtin(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	if (ft_strncmp(cmds->argv[0], "cd", 3) == 0)
		btin_cd(cmds, envsp, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "pwd", 4) == 0)
		btin_pwd(fork_flag);
	else if (ft_strncmp(cmds->argv[0], "export", 7) == 0)
		btin_export(cmds, envsp, 0, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "unset", 6) == 0)
		btin_unset(cmds, envsp, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "echo", 5) == 0)
		btin_echo(cmds, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "env", 4) == 0)
		btin_env(envsp, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "exit", 5) == 0)
		btin_exit(cmds, fork_flag);
	else
		return (0);
	return (1);
}

char	*ex_search_path(char *cmd, t_envs *envsp, int i)
{
	char	**envp_path;
	char	*path;

	while (envsp != NULL && ft_strncmp(envsp->key, "PATH", 5) != 0)
		envsp = envsp->next;
	if (envsp == NULL)
		return (cmd);
	envp_path = ft_split(envsp->value + 5, ':');
	while (envp_path[i] != NULL)
	{
		path = ex_strjoin_c(envp_path[i++], cmd, '/');
		if (path == NULL)
			btin_out(1, errno, strerror(errno));
		if (access(path, F_OK) == 0)
		{
			// free(cmd);
			ex_free_string_array(envp_path);
			return (path);
		}
		free(path);
	}
	ex_free_string_array(envp_path);
	printf("bash: %s: command not found\n", cmd);
	btin_out(1, 127, NULL);
	return (cmd);
}

void	ex_execute(char **cmd, t_envs *envsp, char **envp)
{
	t_envs	*envsp_cp;

	envsp_cp = envsp->next;
	if (access(cmd[0], F_OK) == -1)
		cmd[0] = ex_search_path(cmd[0], envsp_cp, 0);
	execve(cmd[0], cmd, envp);
	btin_out(1, errno, strerror(errno));
}
