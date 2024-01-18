/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mktr_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:54:53 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/18 17:27:38 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	mktr_heredoc_fork(int fd, char *limiter)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"fork", strerror(errno)));
	else if (pid == 0)
	{
		set_signal(MODE_HEREDOC, MODE_HEREDOC);
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
			{
				printf("\033[1A"); // 1줄 위로가는 ANSI 이스케이프 시퀀스
				printf("> ");
				exit(0);
			}
			else if (ft_strncmp(limiter, line, ft_strlen(line) + 1) == 0)
				exit(0);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free(line);
		}
	}
	free(limiter);
	return (pid);
}

int	mktr_heredoc_open_file(char **file_name)
{
	int		fd;
	int		num;
	char	*num_str;

	num = 0;
	while (num < 2147483647)
	{
		num_str = ft_itoa_s(num);
		*file_name = ft_strjoin_s(".tmp", num_str);
		free(num_str);
		if (access(*file_name, F_OK) == 0)
			num++;
		else
		{
			fd = open(*file_name, O_CREAT | O_WRONLY, 0777);
			return (fd);
		}
		free(*file_name);
	}
	*file_name = NULL;
	return (-1);
}

int	mktr_heredoc(char **file_name)
{
	int		fd;
	int		status;
	char	*limiter;

	limiter = *file_name;
	fd = mktr_heredoc_open_file(file_name);
	if (fd == -1)
	{
		free(limiter);
		return (1);
	}
	set_signal(MODE_IGNORE, MODE_IGNORE);
	waitpid(mktr_heredoc_fork(fd, limiter), &status, 0);
	set_signal(MODE_SHELL, MODE_SHELL);
	if (WIFEXITED(status) != 0 && WEXITSTATUS(status) != 0)
		return (1);
	if (WIFSIGNALED(status) != 0)
		return (1);
	return (0);
}
