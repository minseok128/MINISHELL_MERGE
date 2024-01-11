/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_handle_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:07:48 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/10 17:11:12 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ex_dup_to(int from, int to)
{
	if (dup2(from, to) == -1)
		btin_out(1, errno, strerror(errno));
}

void	ex_open_input_fd(t_cmds *cmdsp)
{
	int	in_fd;

	if (access(cmdsp->in_file, F_OK) != 0)
	{
		printf("bash: %s: No such file or directory\n", cmdsp->in_file);
		btin_out(1, 1, NULL);
	}
	in_fd = open(cmdsp->in_file, O_RDONLY);
	if (in_fd == -1)
	{
		printf("bash: %s: Permission denied\n", cmdsp->in_file);
		btin_out(1, 1, NULL);
	}
	ex_dup_to(in_fd, 0);
}

void	ex_open_output_fd(t_cmds *cmdsp)
{
	int	out_fd;

	if (cmdsp->type == APPEND)
		out_fd = open(cmdsp->out_file, O_WRONLY | O_APPEND);
	else
		out_fd = open(cmdsp->out_file, O_WRONLY);
	if (out_fd == -1)
	{
		printf("bash: %s: Permission denied\n", cmdsp->out_file);
		btin_out(1, 1, NULL);
	}
	ex_dup_to(out_fd, 1);
}
