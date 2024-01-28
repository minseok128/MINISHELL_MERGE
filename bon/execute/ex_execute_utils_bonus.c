/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:40:03 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/26 19:58:57 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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

char	*ex_search_path(t_cmds *cmds, t_envs *envsp, char *cmd, int i)
{
	char	**envp_path;
	char	*path;

	while (envsp != NULL && ft_strncmp(envsp->key, "PATH", 5) != 0)
		envsp = envsp->next;
	if (envsp == NULL)
		btin_out(1, 127, btin_make_errmsg("minishell: ", cmd, \
			"No such file or directory"), cmds->enop);
	envp_path = ft_split_s(envsp->value, ':');
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
		"command not found"), cmds->enop);
	return (cmd);
}

void	ex_path_execute_find_error(t_cmds *cmds, char **str, char **path, \
	int i)
{
	char	*cmd;
	char	*pre_path;

	cmd = ((char **)(cmds->argv.items))[0];
	pre_path = *path;
	if (i == 0 && cmd[0] != '/')
		*path = ft_strjoin_s(pre_path, str[i]);
	else
		*path = ex_strjoin_c(pre_path, str[i], '/');
	free(pre_path);
	if (access(*path, F_OK) == -1)
		btin_out(1, 127, btin_make_errmsg("minisehll: ", cmd, \
			"No such file or directory"), cmds->enop);
	if (access(*path, X_OK) == -1)
		btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd, \
			"Permission denied"), cmds->enop);
	if (str[i + 1] != NULL && ex_is_directory(*path) == 0)
		btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd, \
			"Not a directory"), cmds->enop);
	else if (str[i + 1] == NULL && ex_is_directory(*path) == 1)
		btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd, \
			"is a directory"), cmds->enop);
	i++;
}

void	ex_path_execute(t_cmds *cmds, char *cmd)
{
	int		i;
	char	**str;
	char	*path;
	char	*pre_path;

	str = ft_split_s(cmd, '/');
	path = ft_calloc_s(1, sizeof(char));
	if (cmd[0] != '.' && cmd[0] != '/')
	{
		pre_path = path;
		path = ft_strjoin_s("./", path);
		free(pre_path);
	}
	i = 0;
	while (str[i] != NULL)
		ex_path_execute_find_error(cmds, str, &path, i++);
	free(path);
	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}

char	*ex_file_name_execute(t_cmds *cmds, t_envs *envsp, char *cmd)
{
	cmd = ex_search_path(cmds, envsp->next, cmd, 0);
	if (ex_is_directory(cmd) == 1)
		btin_out(1, 127, btin_make_errmsg("minishell: ", cmd, \
			"command not found"), cmds->enop);
	if (access(cmd, X_OK) == -1)
		btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd, \
			"Permission denied"), cmds->enop);
	return (cmd);
}
