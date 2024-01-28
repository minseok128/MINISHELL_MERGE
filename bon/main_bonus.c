/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:05:34 by michang           #+#    #+#             */
/*   Updated: 2024/01/26 20:29:43 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_envs			*envsp;
	t_parser_info	p_info;

	sig_terminal_print_off();
	sig_set(MODE_SHELL, MODE_SHELL);
	envsp = btin_make_envsp(envp);
	parser_info_init(argc, argv, &p_info);
	while (1)
	{
		p_info.line = readline("minishell $ ");
		if (!(p_info.line))
			break ;
		if (*(p_info.line) != 0)
			add_history(p_info.line);
		if (*(p_info.line) != 0 && !ft_jump_white_space(p_info.line))
			if (!tk_tokenize(p_info.line, &(p_info.tk_head), &(p_info.eno)))
				if (!mktr_make_tree(&p_info, &(p_info.hdocs)))
					trtv_list_travel(p_info.root, envsp, &(p_info.eno));
		parser_info_free(&p_info);
	}
	printf("\033[1Aminishell $ exit\n");
	btin_free_envsp(envsp);
	sig_terminal_print_on();
	return (p_info.eno);
}
