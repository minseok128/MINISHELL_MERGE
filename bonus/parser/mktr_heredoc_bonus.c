/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mktr_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:54:53 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/25 16:08:42 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	mktr_heredoc_child(int fd, char *limiter)
{
	char	*line;

	sig_set(MODE_HEREDOC, MODE_HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("\033[1A");
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

pid_t	mktr_heredoc_fork(int fd, char *limiter)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"fork", strerror(errno)));
	else if (pid == 0)
		mktr_heredoc_child(fd, limiter);
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
		*file_name = ft_strjoin_s("./bonus/parser/.tmp", num_str);
		free(num_str);
		if (access(*file_name, F_OK) == 0)
			num++;
		else
		{
			fd = open(*file_name, O_CREAT | O_WRONLY, 0644);
			return (fd);
		}
		free(*file_name);
	}
	return (-1);
}

char	*mktr_heredoc_trim_limiter(char **filename)
{
	int		i;
	int		len;
	char	*limiter;
	char	*new_limiter;

	limiter = *filename;
	len = ft_strlen(limiter);
	if (len < 1)
		return (limiter);
	if ((limiter[0] == '\'' && limiter[len - 1] == '\'') || \
		(limiter[0] == '\"' && limiter[len - 1] == '\"'))
	{
		new_limiter = ft_calloc_s(len - 1, sizeof(char));
		i = 1;
		while (i < len - 1)
		{
			new_limiter[i - 1] = limiter[i];
			i++;
		}
		free(limiter);
		*filename = new_limiter;
		return (new_limiter);
	}
	else
		return (limiter);
}

int	mktr_heredoc(char **file_name)
{
	int		fd;
	int		status;
	char	*limiter;

	limiter = mktr_heredoc_trim_limiter(file_name);
	fd = mktr_heredoc_open_file(file_name);
	if (fd == -1)
	{
		free(limiter);
		return (1);
	}
	sig_set(MODE_IGNORE, MODE_IGNORE);
	waitpid(mktr_heredoc_fork(fd, limiter), &status, 0);
	sig_set(MODE_SHELL, MODE_SHELL);
	if (WIFEXITED(status) != 0 && WEXITSTATUS(status) != 0)
		return (1);
	if (WIFSIGNALED(status) != 0)
		return (1);
	return (0);
}
