/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:05:34 by michang           #+#    #+#             */
/*   Updated: 2024/01/21 19:17:21 by seonjo           ###   ########.fr       */
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

void	leaks_test()
{
	system("leaks --list -- minishell");
}

void	trtv_node_free(t_tr_node *node)
{
	int	i;

	if (!node)
		return ;
	trtv_node_free(node->left);
	trtv_node_free(node->right);
	if (node->word_split)
	{
		i = 0;
		while (i < node->word_split->size)
		{
			if (node->word_split->items[i])
				free(node->word_split->items[i]);
			i++;	
		}	
		vec_free(node->word_split);
		free(node->word_split);
	}
	free (node);
}

void	parser_info_free(t_parser_info *p_info)
{
	t_token	*t_node;

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
}

int	main(int argc, char **argv, char **envp)
{
	t_envs			*envsp;
	t_parser_info	p_info;

	atexit(leaks_test);
	argc = argv - argv + argc;
	terminal_print_off();
	set_signal(MODE_SHELL, MODE_SHELL);
	envsp = btin_make_envsp(envp);
	while (1)
	{
		ft_bzero(&p_info, sizeof(t_parser_info));
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
		parser_info_free(&p_info);
	}
	btin_free_envsp(envsp);
	terminal_print_on();
}
