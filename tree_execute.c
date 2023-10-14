/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:17:18 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 20:59:39 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*tr_free2(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	return (NULL);
}

char	*tr_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len1;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1) + 1;
	str = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (str == 0)
		return (0);
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = '/';
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*tr_renew_path(char *path)
{
	char	*pwd;

	if (access(path, F_OK) == -1)
		return (NULL);
	cd_cd(path);
	pwd = getcwd(NULL, 1024);
	if (pwd == NULL)
		en_error();
	free(path);
	return (pwd);
}

char	*tr_check_path(char **cmd, char **envp)
{
	int		i;
	char	**envp_path;
	char	*path;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	envp_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (envp_path[i] != NULL)
	{
		path = tr_strjoin(envp_path[i++], cmd[0]);
		if (path == NULL)
			error(NULL, 1);
		if (access(path, F_OK) == 0)
		{
			tr_free2(envp_path);
			return (path);
		}
		free(path);
	}
	tr_free2(envp_path);
	return (cmd);
}

void	tr_execute(t_tree *tree, char **envp)
{
	char	**cmd;
	char	*file;

	cmd = ft_split(tree->str, ' ');
	if (cmd == NULL)
		error(NULL, 1);
	file = tr_renew_path(cmd[0]);
	if (file == NULL)
		file = tr_check_path(cmd, envp);
	if (execve(file, cmd, NULL) == -1)
		en_error();
}
