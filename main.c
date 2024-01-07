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
#include "btin/btin.h"

void	trem_init(int argc, char **argv)
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

int	jump_white_space(char *str)
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
	t_envs			*envsp;
	struct termios	term;
	t_parser_info	p_info;

	tcgetattr(STDIN_FILENO, &term);
	trem_init(argc, argv);
	envsp = btin_make_envsp(envp);
	btin_env(envsp);
	while (1)
	{
		p_info.line = readline("minishell $ ");
		if (!(p_info.line))
			break ;
		if (*(p_info.line) != 0)
			add_history(p_info.line);
		if (*(p_info.line) != 0 && !jump_white_space(p_info.line))
		{
			if (!tk_tokenize(p_info.line, &(p_info.tk_head)))
				if (!mktr_make_tree(p_info.tk_head, &(p_info.root)))
					(p_info.root, envsp);
		}
		free(p_info.line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
