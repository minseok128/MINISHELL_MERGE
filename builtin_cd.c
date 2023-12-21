/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:35 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/21 19:39:58 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_go_directory(char *path)
{
	struct stat	dir_stat;

	if (stat(path, &dir_stat) == -1)
		bi_error();
	if (S_ISDIR(dir_stat.st_mode) != 1)
		return (2);
	if (access(path, X_OK) != 0)
		return (3);
	//free(dir_stat);
	if (chdir(path) == -1)
		bi_error();
	return (0);
}

void	cd_errmsg(int flag, char *cmd)
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
}

void	builtin_cd(t_cmd cmd, t_envp *envp)
{
	int		flag;

	flag = 0;
	if (cmd.command[1] == NULL)
		
	if (access(cmd[0], F_OK) == -1)
		bi_errmsg(1, cmd);
	else
	{
		flag = bi_go_dir(cmd);
		if (flag != 0)
			bi_errmsg(flag, cmd);
	}
}
