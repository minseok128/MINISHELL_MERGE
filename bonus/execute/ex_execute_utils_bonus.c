/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:40:03 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/25 14:29:53 by seonjo           ###   ########.fr       */
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

void	ex_path_execute_find_error(char **str, char *path, \
	char *pre_path, char *cmd)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		pre_path = path;
		if (i == 0 && cmd[0] != '/')
			path = ft_strjoin_s(pre_path, str[i]);
		else
			path = ex_strjoin_c(pre_path, str[i], '/');
		free(pre_path);
		if (access(path, F_OK) == -1)
			btin_out(1, 127, btin_make_errmsg("minisehll: ", cmd, \
				"No such file or directory"));
		if (access(path, X_OK) == -1)
			btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd, \
				"Permission denied"));
		if (str[i + 1] != NULL && ex_is_directory(path) == 0)
			btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd, \
				"Not a directory"));
		else if (str[i + 1] == NULL && ex_is_directory(path) == 1)
			btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd, \
				"is a directory"));
		i++;
	}
}

void	ex_path_execute(char *cmd)
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
	ex_path_execute_find_error(str, path, NULL, cmd);
	free(path);
	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}

char	*ex_file_name_execute(char *cmd, t_envs *envsp)
{
	cmd = ex_search_path(cmd, envsp->next, 0);
	if (ex_is_directory(cmd) == 1)
		btin_out(1, 127, btin_make_errmsg("minishell: ", cmd, \
			"command not found"));
	if (access(cmd, X_OK) == -1)
		btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd, \
			"Permission denied"));
	return (cmd);
}
