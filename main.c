/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:05:34 by michang           #+#    #+#             */
/*   Updated: 2024/01/15 17:19:56 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_parser_info	p_info;

	argc = argv - argv + argc;
	terminal_print_off();
	set_signal(MODE_SHELL, MODE_SHELL);
	envsp = btin_make_envsp(envp);
	while (1)
	{
		p_info.line = readline("minishell $ ");
		if (!(p_info.line))
			break ;
		if (*(p_info.line) != 0)
			add_history(p_info.line);
		if (*(p_info.line) != 0 && !jump_white_space(p_info.line))
			if (!tk_tokenize(p_info.line, &(p_info.tk_head)))
				if (!mktr_make_tree(p_info.tk_head, &(p_info.root)))
					if (!trtv_expansion_travel(p_info.root, envsp))
						trtv_list_travel(p_info.root, envsp);
		free(p_info.line);
	}
	terminal_print_on();
}
