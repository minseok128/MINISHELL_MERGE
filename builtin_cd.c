/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:35 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/22 19:27:09 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_pwd(t_envp *envp_head, char *dest)
{
	t_envp	*pwd;
	t_envp	*oldpwd;

	pwd = find_node(envp_head, "PWD");
	oldpwd = find_node(envp_head, "OLDPWD");
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

void	move_to_dest(t_envp *envp_head, char *dest)
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
		modify_pwd(envp_head, dest);
}

void	builtin_cd(t_cmd *cmd, t_envp *envp_head)
{
	t_envp	*home;
	char	*dest;

	errno = 0;
	if (cmd->command[1] == NULL)
	{
		home = find_node(envp_head, "HOME");
		if (home == NULL)
		{
			cd_error(4, NULL);
			return ;
		}
		dest = ft_strdup(home->value);
	}
	else
		dest = ft_strdup(cmd->command[1]);
	if (access(dest, F_OK) == -1)
		cd_error(1, dest);
	else
		move_to_dest(envp_head, dest);
}
