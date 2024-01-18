/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:05:34 by michang           #+#    #+#             */
/*   Updated: 2024/01/12 16:12:31 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		errno = 1;
		// exit(1);
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_heredoc_handler(int signo)
{
	(void)signo;
	printf("\n");
	exit(1);
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == MODE_SHELL)
		signal(SIGINT, signal_handler);
	if (sig_quit == MODE_SHELL)
		signal(SIGQUIT, signal_handler);
	if (sig_int == MODE_DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_quit == MODE_DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_int == MODE_IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_quit == MODE_IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_int == MODE_HEREDOC)
		signal(SIGINT, signal_heredoc_handler);
	if (sig_quit == MODE_HEREDOC)
		signal(SIGQUIT, SIG_IGN);
}

void	terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	terminal_print_on(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	is_white_space(char *str)
{
	while (*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
			return (0);
		str++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_envp			*envp_head;
	char			*line;
	struct termios	term;

	argv[0] = NULL;
	argc = 0;
	tcgetattr(STDIN_FILENO, &term);
	terminal_print_off();
	envp_head = make_envp(envp);
	builtin_env(envp_head);
	while (1)
	{
		set_signal(MODE_SHELL, MODE_SHELL);
		line = readline("minishell $ ");
		if (!line)
		{
			printf("\033[1A");
			printf("\033[12C");
			printf("exit\n");
			break;
		}
		if (*line != 0)
			add_history(line);
		if (is_white_space(line))
		{
			printf("this line is whitespace\n");
		}
		else if (ft_strncmp(line, "heredoc", 7) == 0)
		{
			set_signal(MODE_IGNORE, MODE_IGNORE);
			int pid = fork();
			if (pid == 0)
			{
				set_signal(MODE_HEREDOC, MODE_IGNORE);
				while (1)
				{
					char *line2 = readline("> ");
					if (line2 == NULL)
					{
						printf("\033[1A"); // 1줄 위로가는 ANSI 이스케이프 시퀀스
						printf("> ");
						exit(0);
					}
					printf("%s\n", line2);
					free(line2);
				}
				exit(0);
			}
			waitpid(pid, NULL, 0);
		}
		else if (ft_strncmp(line, "fork", 5) == 0)
		{
			set_signal(MODE_IGNORE, MODE_IGNORE);
			int pid = fork();
			if (pid == 0)
			{
				set_signal(MODE_DEFAULT, MODE_DEFAULT);
				terminal_print_on();
				char *cmd[] = {"/bin/cat", NULL};
				execv(cmd[0], cmd);
			}
			int status = 0;
			waitpid(pid, &status, 0);
			// if (status & 0x7F){  하위 7비트가 0이 아닌경우 , signal로 인한 종료
				int signal_number = status & 0x7F;
				if (signal_number == SIGINT)
					printf("\n");
				else if (signal_number == SIGQUIT)
					printf("Quit: 3\n");
			terminal_print_off();
			//하위 8비트는 시그널 종류
			//상위 8비트는 종료 상태
		}
		else if (ft_strncmp(line, "errno", 6) == 0)
		{
			printf("before errno : %d\n", errno);
			if (errno == 0)
				errno = 5;
			else
				errno = 0;
			printf("after errno : %d\n", errno);
		}
		free(line);
	}
	terminal_print_on();
}
