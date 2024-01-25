/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:47 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/25 11:11:37 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trtv_redir_s_l(t_cmds *cmd, char *file)
{
	int	fd;

	if ((cmd->type & RD_HEREDOC) != 0)
		if (unlink(cmd->in_file) == -1)
			btin_out(1, errno, btin_make_errmsg("minishell: ", \
				"unlink", strerror(errno)));
	cmd->in_file = file;
	cmd->type &= ~RD_HEREDOC;
	fd = open(cmd->in_file, O_RDONLY);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}

int	trtv_redir_s_r(t_cmds *cmd, char *file)
{
	int	fd;

	cmd->out_file = file;
	cmd->type &= ~RD_APPEND;
	fd = open(cmd->out_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}

int	trtv_redir_d_l(t_cmds *cmd, char *file)
{
	int		fd;

	if ((cmd->type & RD_HEREDOC) != 0)
		if (unlink(cmd->in_file) == -1)
			btin_out(1, errno, btin_make_errmsg("minishell: ", \
				"unlink", strerror(errno)));
	cmd->in_file = file;
	cmd->type |= RD_HEREDOC;
	fd = open(cmd->in_file, O_RDONLY);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}

int	trtv_redir_d_r(t_cmds *cmd, char *file)
{
	int	fd;

	cmd->out_file = file;
	cmd->type |= RD_APPEND;
	fd = open(cmd->out_file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}
