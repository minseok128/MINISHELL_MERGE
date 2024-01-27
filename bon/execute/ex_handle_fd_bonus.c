/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_handle_fd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:07:48 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/26 19:44:19 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	ex_dup_to(t_cmds *cmds, int from, int to)
{
	if (dup2(from, to) == -1)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"dup2", strerror(errno)), cmds->enop);
}

void	ex_open_input_fd(t_cmds *cmdsp)
{
	int	in_fd;

	if (access(cmdsp->in_file, F_OK) != 0)
		btin_out(1, 1, btin_make_errmsg("minishell: ", cmdsp->in_file, \
			"No such file or directory"), cmdsp->enop);
	in_fd = open(cmdsp->in_file, O_RDONLY);
	if (in_fd == -1)
		btin_out(1, 1, btin_make_errmsg("minishell: ", cmdsp->in_file, \
			strerror(errno)), cmdsp->enop);
	ex_dup_to(cmdsp, in_fd, 0);
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
			strerror(errno)), cmdsp->enop);
	ex_dup_to(cmdsp, out_fd, 1);
}

int	ex_open_btin_output_fd(t_cmds *cmds)
{
	int	std_out;
	int	out_fd;

	if ((cmds->type & RD_APPEND) != 0)
		out_fd = open(cmds->out_file, O_WRONLY | O_APPEND);
	else
		out_fd = open(cmds->out_file, O_WRONLY);
	if (out_fd == -1)
	{
		btin_out(1, 1, btin_make_errmsg("minishell: ", cmds->out_file, \
			strerror(errno)), cmds->enop);
		return (-1);
	}
	std_out = dup(1);
	ex_dup_to(cmds, out_fd, 1);
	close(out_fd);
	return (std_out);
}

int	ex_open_btin_input_fd(t_cmds *cmds)
{
	int	std_in;
	int	in_fd;

	if (access(cmds->in_file, F_OK) != 0)
	{
		btin_out(0, 1, btin_make_errmsg("minishell: ", cmds->in_file, \
			"No such file or directory"), cmds->enop);
		return (-1);
	}
	in_fd = open(cmds->in_file, O_RDONLY);
	if (in_fd == -1)
	{
		btin_out(0, 1, btin_make_errmsg("minishell: ", cmds->in_file, \
			strerror(errno)), cmds->enop);
		return (-1);
	}
	std_in = dup(0);
	ex_dup_to(cmds, in_fd, 0);
	close(in_fd);
	return (std_in);
}
