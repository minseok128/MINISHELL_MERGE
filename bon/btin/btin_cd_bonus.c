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

#include "../minishell_bonus.h"

char	**btin_make_arr(char *s1, char *s2)
{
	char	**arr;

	arr = ft_calloc_s(2, sizeof(char *));
	arr[0] = s1;
	arr[1] = s2;
	return (arr);
}

void	btin_modify_pwd(t_cmds *cmds, t_envs *envsp, char *old_pwd, \
	int fork_flag)
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
	else
		free(old_pwd);
	if (env_pwd != NULL)
	{
		pwd = getcwd(NULL, 1024);
		if (pwd == NULL)
			btin_out(1, errno, btin_make_errmsg("minishell: cd: ", \
				"getcwd", strerror(errno)), cmds->enop);
		free(env_pwd->value);
		env_pwd->value = pwd;
	}
	btin_out(fork_flag, 0, NULL, cmds->enop);
}

void	btin_cd_error(t_cmds *cmds, char **arr_dp, int flag, int fork_flag)
{
	char	*errmsg;

	errmsg = NULL;
	if (flag == 1)
		errmsg = btin_make_errmsg("minishell: cd: ", arr_dp[0], \
			"No such file or directory");
	else if (flag == 2)
		errmsg = btin_make_errmsg("minishell: cd: ", arr_dp[0], \
			"Not a directory");
	else if (flag == 3)
		errmsg = btin_make_errmsg("minishell: cd: ", arr_dp[0], \
			"Permission denied");
	else if (flag == 4)
		errmsg = btin_make_errmsg("minishell: ", "cd", "HOME not set");
	if (arr_dp[0] != NULL)
		free(arr_dp[0]);
	if (arr_dp[1] != NULL)
		free(arr_dp[1]);
	free(arr_dp);
	btin_out(fork_flag, 1, errmsg, cmds->enop);
}

void	btin_move_to_dest(t_cmds *cmds, t_envs *envsp, char *dest, \
	int fork_flag)
{
	struct stat	dir_stat;
	char		*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd == NULL)
		btin_out(1, errno, btin_make_errmsg("minishell: cd: ", \
			"getcwd", strerror(errno)), cmds->enop);
	if (stat(dest, &dir_stat) == -1)
		btin_out(1, errno, btin_make_errmsg("minishell: cd: ", \
		"stat", strerror(errno)), cmds->enop);
	else if (S_ISDIR(dir_stat.st_mode) != 1)
		btin_cd_error(cmds, btin_make_arr(dest, pwd), 2, fork_flag);
	else if (access(dest, X_OK) != 0)
		btin_cd_error(cmds, btin_make_arr(dest, pwd), 3, fork_flag);
	else if (chdir(dest) == -1)
		btin_out(1, errno, btin_make_errmsg("minishell: cd: ", \
		"chdir", strerror(errno)), cmds->enop);
	else
	{
		free(dest);
		btin_modify_pwd(cmds, envsp, pwd, fork_flag);
	}
}

void	btin_cd(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	t_envs	*home;
	char	*dest;

	if (cmds->argv.items[1] == NULL)
	{
		home = btin_find_node(envsp, "HOME");
		if (home == NULL || home->value == NULL)
		{
			btin_cd_error(cmds, btin_make_arr(NULL, NULL), 4, fork_flag);
			return ;
		}
		dest = ft_strdup_s(home->value);
	}
	else
		dest = ft_strdup_s(cmds->argv.items[1]);
	if (access(dest, F_OK) == -1)
		btin_cd_error(cmds, btin_make_arr(dest, NULL), 1, fork_flag);
	else
		btin_move_to_dest(cmds, envsp, dest, fork_flag);
}
