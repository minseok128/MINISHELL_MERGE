/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:05:34 by michang           #+#    #+#             */
/*   Updated: 2023/09/08 15:05:35 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_term(int argc, char **argv)
{
	struct termios term;

	if (argc != 1)
		exit(1);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal(MODE_SHELL, MODE_SHELL);
	(void) argv;
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
	char			*line;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	initialize_term(argc, argv);
	(void) envp;
	while (1)
	{
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line != 0)
			add_history(line);
		if (*line != 0 && !is_white_space(line))
		{
			parse(line);			
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
