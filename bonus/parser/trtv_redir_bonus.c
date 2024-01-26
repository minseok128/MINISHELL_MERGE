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

#include "../minishell_bonus.h"

int	trtv_redir_l(t_cmds *cmd, t_vector *word_split)
{
	int	fd;

	if (word_split->size > 1)
	{
		cmd->type |= RD_AMBIGUOUS;
		return (1);
	}
	cmd->in_file = word_split->items[0];
	fd = open(cmd->in_file, O_RDONLY);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}

int	trtv_redir_s_r(t_cmds *cmd, t_vector *word_split)
{
	int	fd;

	if (word_split->size > 1)
	{
		cmd->type |= RD_AMBIGUOUS;
		return (1);
	}
	cmd->out_file = word_split->items[0];
	cmd->type &= ~RD_APPEND;
	fd = open(cmd->out_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}

int	trtv_redir_d_r(t_cmds *cmd, t_vector *word_split)
{
	int	fd;

	if (word_split->size > 1)
	{
		cmd->type |= RD_AMBIGUOUS;
		return (1);
	}
	cmd->out_file = word_split->items[0];
	cmd->type |= RD_APPEND;
	fd = open(cmd->out_file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (1);
	else
		close(fd);
	return (0);
}
