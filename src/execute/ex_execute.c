/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:12:59 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/29 11:33:25 by seonjo           ###   ########.fr       */
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

void	ex_execute(t_cmds *cmds, t_envs *envsp, char **envp)
{
	t_envs	*envsp_cp;
	char	**cmd;

	cmd = (char **)cmds->argv.items;
	envsp_cp = envsp->next;
	if (ft_strncmp(cmd[0], ".", 2) == 0)
		btin_out(1, 2, btin_make_errmsg("minishell: ", cmd[0], "filename \
			argument required\n.: usage: . filename [arguments]"), cmds->enop);
	else if (ft_strncmp(cmd[0], "..", 3) == 0 || cmd[0][0] == '\0')
		btin_out(1, 127, btin_make_errmsg("minishell: ", cmd[0], \
			"command not found"), cmds->enop);
	if (ft_strncmp(cmd[0], "/", 2) == 0)
		btin_out(1, 126, btin_make_errmsg("minisehll: ", cmd[0], \
			"is a directory"), cmds->enop);
	if (ex_is_path(cmd[0]) == 1)
		ex_path_execute(cmds, cmd[0]);
	else
		cmd[0] = ex_file_name_execute(cmds, envsp, cmd[0]);
	execve(cmd[0], cmd, envp);
	btin_out(1, errno, btin_make_errmsg("minishell: ", cmd[0], \
			strerror(errno)), cmds->enop);
}
