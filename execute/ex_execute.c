/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:12:59 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/25 11:17:31 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ex_search_path(char *cmd, t_envs *envsp, int i)
{
	char	**envp_path;
	char	*path;

	while (envsp != NULL && ft_strncmp(envsp->key, "PATH", 5) != 0)
		envsp = envsp->next;
	if (envsp == NULL)
		btin_out(1, 127, btin_make_errmsg("minishell: ", cmd, \
			"No such file or directory"));
	envp_path = ft_split(envsp->value, ':');
	while (envp_path[i] != NULL)
	{
		path = ex_strjoin_c(envp_path[i++], cmd, '/');
		if (access(path, F_OK) == 0)
		{
			free(cmd);
			ex_free_string_array(envp_path);
			return (path);
		}
		free(path);
	}
	ex_free_string_array(envp_path);
	btin_out(1, 127, btin_make_errmsg("minishell: ", cmd, \
		"command not found"));
	return (cmd);
}

int	ex_is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ex_is_directory(char *cmd)
{
	struct stat	buf;

	if (stat(cmd, &buf) == -1)
		return (0);
	if (S_ISDIR(buf.st_mode) == 0)
		return (0);
	else
		return (1);
}

void	ex_execute(char **cmd, t_envs *envsp, char **envp)
{
	t_envs	*envsp_cp;

	envsp_cp = envsp->next;
	if (ft_strncmp(cmd[0], ".", 2) == 0)
		btin_out(1, 2, btin_make_errmsg("minishell: ", cmd[0], \
			"filename argument required\n.: usage: . filename [arguments]"));
	else if (ft_strncmp(cmd[0], "..", 3) == 0 || cmd[0][0] == '\0')
		btin_out(1, 127, btin_make_errmsg("minishell: ", cmd[0], \
			"command not found"));
	if (ex_is_directory(cmd[0]) == 1 && ex_is_path(cmd[0]) == 1)
		btin_out(1, 126, btin_make_errmsg("minishell: ", cmd[0], \
			"is a directory"));
	else if (access(cmd[0], F_OK) == -1)
	{
		if (ex_is_path(cmd[0]) == 1)
			btin_out(1, 127, btin_make_errmsg("minisehll: ", cmd[0], \
				"No such file or directory"));
		else
			cmd[0] = ex_search_path(cmd[0], envsp_cp, 0);
	}
	execve(cmd[0], cmd, envp);
	btin_out(1, errno, btin_make_errmsg("minishell: ", cmd[0], \
			strerror(errno)));
}
