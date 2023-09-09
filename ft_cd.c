/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:32:13 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/09 15:36:54 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_root(char *path)
{
	while (path[0] != '/' && path[1] != '\0')
	{
		if (chdir("..") == -1)
			error_and_exit();
		free(path);
		path = getcwd(NULL, 1024);
		if (path == NULL)
			error_and_exit();
	}
}

int	find_dir(char *dest)
{
	int				flag;
	DIR				*dir;
	struct dirent	*subdir;

	flag = 1;
	dir = opendir(getcwd(NULL, 1024));
	if (dir == NULL)
		error_and_exit();
	subdir = readdir(dir);
	while (subdir != NULL)
	{
		if (ft_strncmp(dest, subdir -> d_name, ft_strlen(dest) + 1) == 0)
		{
			//dirent_free(subdir);
			flag = 0;
			break ;
		}
		//dirent_free(subdir);
		subdir = readdir(dir);
	}
	if (closedir(dir) == -1)
		error_and_exit();
	return (flag);
}

int	go_dir(char *path, char *dest)
{
	int			flag;
	char		*new_path;
	struct stat	*dir_stat;

	flag = 0;
	new_path = ft_strjoin(path, dest);
	if (new_path == NULL)
		error_and_exit();
	free(path);
	path = new_path;
	dir_stat = NULL;
	lstat(path, dir_stat);
	if (!S_ISDIR(dir_stat -> st_mode))
		flag = 2;
	if (access(path, X_OK) != 1)
		flag = 3;
	//free(dir_stat);
	return (flag);
}

int	absolute_path(char *path)
{
	int		i;
	int		flag;
	char	**arr;

	arr = ft_split(path, '/');
	move_root(path);
	printf("%s\n\n\n", getcwd(NULL, 1024));
	i = 0;
	while (arr[i] != NULL)
	{
		flag = find_dir(arr[i]);
		if (flag == 0)
			flag = go_dir(path, arr[i]);
		if (flag != 0)
			break ;
		free(arr[i]);
		i++;
	}
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return (flag);
}

int	relative_path(char *path)
{
	(void)path;
	return 0;
}

void	errflag_exe(int flag, char *cmd, char *pwd)
{
	if (flag == 0)
		return ;
	if (flag == 1)
		printf("bash: cd: %s: No such file or directory\n", cmd);
	else if (flag == 2)
		printf("bash: cd: %s: Not a directory\n", cmd);
	else if (flag == 3)
		printf("bash: cd: %s: Permission denied\n", cmd);
	errno = 1;
	(void)pwd;
	//ft_cd(pwd);
}

void	ft_cd(char *cmd)
{

}
