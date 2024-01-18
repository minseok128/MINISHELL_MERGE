/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:35 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 18:53:33 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	btin_modify_pwd(t_envs *envsp, char *old_pwd, int fork_flag)
{
	t_envs	*env_pwd;
	t_envs	*env_oldpwd;
	char	*pwd;

	env_pwd = btin_find_node(envsp, "PWD");
	env_oldpwd = btin_find_node(envsp, "OLDPWD");
	if (env_oldpwd != NULL)
	{
		free(env_oldpwd->value);
		env_oldpwd->value = old_pwd;
	}
	if (env_pwd != NULL)
	{
		pwd = getcwd(NULL, 1024);
		if (pwd == NULL)
			btin_out(1, errno, btin_make_errmsg("minishell: ", \
				"getcwd", strerror(errno)));
		free(env_pwd->value);
		env_pwd->value = pwd;
	}
	btin_out(fork_flag, 0, NULL);
}

void	btin_cd_error(int flag, char *dest, char *pwd, int fork_flag)
{
	char	*errmsg;

	errmsg = NULL;
	if (flag == 0)
		return ;
	if (flag == 1)
		errmsg = btin_make_errmsg("minishell: cd: ", dest, \
			"No such file or directory");
	else if (flag == 2)
		errmsg = btin_make_errmsg("minishell: cd: ", dest, \
			"Not a directory");
	else if (flag == 3)
		errmsg = btin_make_errmsg("minishell: cd: ", dest, \
			"Permission denied");
	else if (flag == 4)
		errmsg = btin_make_errmsg("minishell: ", "cd", "HOME not set");
	if (dest != NULL)
		free(dest);
	if (pwd != NULL)
		free(pwd);
	btin_out(fork_flag, 1, errmsg);
}

void	btin_move_to_dest(t_envs *envsp, char *dest, int fork_flag)
{
	struct stat	dir_stat;
	char		*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd == NULL)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"getcwd", strerror(errno)));
	if (stat(dest, &dir_stat) == -1)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
		"stat", strerror(errno)));
	else if (S_ISDIR(dir_stat.st_mode) != 1)
		btin_cd_error(2, dest, pwd, fork_flag);
	else if (access(dest, X_OK) != 0)
		btin_cd_error(3, dest, pwd, fork_flag);
	else if (chdir(dest) == -1)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
		"chdir", strerror(errno)));
	else
	{
		free(dest);
		btin_modify_pwd(envsp, pwd, fork_flag);
	}
}

void	btin_cd(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	t_envs	*home;
	char	*dest;

	if (cmds->argv.items[1] == NULL)
	{
		home = btin_find_node(envsp, "HOME");
		if (home == NULL)
		{
			btin_cd_error(4, NULL, NULL, fork_flag);
			return ;
		}
		dest = ft_strdup_s(home->value);
	}
	else
		dest = ft_strdup_s(cmds->argv.items[1]);
	if (access(dest, F_OK) == -1)
		btin_cd_error(1, dest, NULL, fork_flag);
	else
		btin_move_to_dest(envsp, dest, fork_flag);
}
