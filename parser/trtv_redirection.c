/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:11:47 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/18 17:16:29 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trtv_redir_s_l(t_cmds *cmd, char *file)
{
	int	fd;
	
	// 1. 만약 heredoc이 열려있으면 파일 삭제
	if ((cmd->type & RD_HEREDOC) != 0)
		if (unlink(cmd->in_file) == -1)
			btin_out(1, errno, btin_make_errmsg("minishell: ", \
				"unlink", strerror(errno)));
	// 2. 구조체에 in_file과 type 초기화
	if (cmd->in_file != NULL)
		free(cmd->in_file);
	cmd->in_file = ft_strdup_s(file);
	cmd->type &= ~RD_HEREDOC;
	// 3. 파일 오픈
	fd = open(cmd->in_file, O_RDONLY);
	// 4. 파일 오픈 실패시 구조체 만들기 stop
	if (fd == -1)
	{
		return (-1);
		// 구조체 만들기 stop
	}
	// 5. 파일 오픈 성공시 바로 닫기
	else
		close(fd);
	return (0);
}

int	trtv_redir_s_r(t_cmds *cmd, char *file)
{
	int	fd;
	
	// 1. 구조체에 out_file과 type 초기화
	if (cmd->out_file != NULL)
		free(cmd->out_file);
	cmd->out_file = ft_strdup_s(file);
	cmd->type &= ~RD_APPEND;
	// 2. 파일 오픈
	fd = open(cmd->out_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	// 3. 파일 오픈 실패시 구조체 만들기 stop
	if (fd == -1)
	{
		return (-1);
		// 구조체 만들기 stop
	}
	// 4. 파일 오픈 성공시 바로 닫기
	else
		close(fd);
	return (0);
}

int	trtv_redir_d_l(t_cmds *cmd, char *file)
{
	int		fd;

	// 1. 만약 heredoc이 열려있으면 파일 삭제
	if ((cmd->type & RD_HEREDOC) != 0)
		if (unlink(cmd->in_file) == -1)
			btin_out(1, errno, btin_make_errmsg("minishell: ", \
				"unlink", strerror(errno)));
	// 2. 구조체에 in_file과 type 초기화
	if (cmd->in_file != NULL)
		free(cmd->in_file);
	cmd->in_file = ft_strdup_s(file);
	cmd->type |= RD_HEREDOC;
	// 3. 파일 오픈
	fd = open(cmd->in_file, O_RDONLY);
	// 4. 파일 오픈 실패시 구조체 만들기 stop
	if (fd == -1)
	{
		return (-1);
		// 구조체 만들기 stop
	}
	// 5. 파일 오픈 성공시 바로 닫기
	else
		close(fd);
	return (0);
}

int	trtv_redir_d_r(t_cmds *cmd, char *file)
{
	int	fd;
	
	// 1. 구조체에 out_file과 type 초기화
	if (cmd->out_file != NULL)
		free(cmd->out_file);
	cmd->out_file = ft_strdup_s(file);
	cmd->type |= RD_APPEND;
	// 2. 파일 오픈
	fd = open(cmd->out_file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	// 3. 파일 오픈 실패시 구조체 만들기 stop
	if (fd == -1)
	{
		return (-1);
		// 구조체 만들기 stop
	}
	// 4. 파일 오픈 성공시 바로 닫기
	else
		close(fd);
	return (0);
}
