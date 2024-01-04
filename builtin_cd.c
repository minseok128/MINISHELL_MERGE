/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:35 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:26:29 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_pwd(t_envs *envsp, char *dest)
{
	t_envs	*pwd;
	t_envs	*oldpwd;

	pwd = find_node(envsp, "PWD");
	oldpwd = find_node(envsp, "OLDPWD");
	if (oldpwd != NULL && pwd != NULL)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = dest;
	}
	else
		free(dest);
}

void	cd_error(int flag, char *dest)
{
	if (flag == 0)
		return ;
	if (flag == 1)
		printf("bash: cd: %s: No such file or directory\n", dest);
	else if (flag == 2)
		printf("bash: cd: %s: Not a directory\n", dest);
	else if (flag == 3)
		printf("bash: cd: %s: Permission denied\n", dest);
	else if (flag == 4)
		printf("bash: cd: HOME not set\n");
	if (dest != NULL)
		free(dest);
	errno = 1;
}

void	move_to_dest(t_envs *envsp, char *dest)
{
	struct stat	dir_stat;

	if (stat(dest, &dir_stat) == -1)
		builtin_error();
	else if (S_ISDIR(dir_stat.st_mode) != 1)
		cd_error(2, dest);
	else if (access(dest, X_OK) != 0)
		cd_error(3, dest);
	else if (chdir(dest) == -1)
		builtin_error();
	else
		modify_pwd(envsp, dest);
}

void	builtin_cd(t_cmds *cmds, t_envs *envsp)
{
	t_envs	*home;
	char	*dest;

	errno = 0;
	if (cmds->argv[1] == NULL)
	{
		home = find_node(envsp, "HOME");
		if (home == NULL)
		{
			cd_error(4, NULL);
			return ;
		}
		dest = ft__strdup(home->value);
	}
	else
		dest = ft__strdup(cmds->argv[1]);
	if (access(dest, F_OK) == -1)
		cd_error(1, dest);
	else
		move_to_dest(envsp, dest);
}
