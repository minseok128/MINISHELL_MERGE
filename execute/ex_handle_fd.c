/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_handle_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:07:48 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/17 17:44:17 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ex_dup_to(int from, int to)
{
	if (dup2(from, to) == -1)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"dup2: ", strerror(errno)));
}

void	ex_open_input_fd(t_cmds *cmdsp)
{
	int	in_fd;

	if (access(cmdsp->in_file, F_OK) != 0)
		btin_out(1, 1, btin_make_errmsg("minishell: ", cmdsp->in_file, \
			": No such file or directory\n"));
	in_fd = open(cmdsp->in_file, O_RDONLY);
	if (in_fd == -1)
		btin_out(1, 1, btin_make_errmsg("minishell: ", cmdsp->in_file, \
			": Permission denied\n"));
	ex_dup_to(in_fd, 0);
}

void	ex_open_output_fd(t_cmds *cmdsp)
{
	int	out_fd;

	if ((cmdsp->type & RD_APPEND) != 0)
		out_fd = open(cmdsp->out_file, O_WRONLY | O_APPEND);
	else
		out_fd = open(cmdsp->out_file, O_WRONLY);
	if (out_fd == -1)
		btin_out(1, 1, btin_make_errmsg("minishell: ", cmdsp->out_file, \
			": Permission denied\n"));
	ex_dup_to(out_fd, 1);
}
