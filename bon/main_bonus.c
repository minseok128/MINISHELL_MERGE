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

void	parser_info_init(int argc, char **argv, t_parser_info *p_info)
{
	p_info->eno = (argv - argv) + (argc - argc);
	g_signal = &(p_info->eno);
	ft_parser_info_zero(p_info);
}

void	parser_info_free(t_parser_info *p_info)
{
	t_token	*t_node;
	int		i;

	i = 0;
	while (p_info->hdocs && i < p_info->hdocs->size)
	{
		unlink(p_info->hdocs->items[i]);
		free(p_info->hdocs->items[i++]);
	}
	vec_free(p_info->hdocs);
	free(p_info->hdocs);
	free(p_info->line);
	t_node = p_info->tk_head;
	while (p_info->tk_head)
	{
		t_node = p_info->tk_head;
		if (t_node->str)
			free(t_node->str);
		p_info->tk_head = p_info->tk_head->next;
		free(t_node);
	}
	trtv_node_free(p_info->root);
	ft_parser_info_zero(p_info);
}

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
