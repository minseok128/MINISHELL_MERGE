/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:45:30 by michang           #+#    #+#             */
/*   Updated: 2024/01/28 15:45:31 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	parser_info_init(int argc, char **argv, t_parser_info *p_info)
{
	p_info->eno = (argv - argv) + (argc - argc);
	g_signal = &(p_info->eno);
	ft_parser_info_zero(p_info);
	printf("\n");
	printf("\t  ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄   \n");
	printf("\t▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███  \n");
	printf("\t███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███  \n");
	printf("\t███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄\n");
	printf("\t███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀ \n");
	printf("\t███   ███   ███ ███  ███   ███ ███           ███   ███    ███  \n");
	printf("\t███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███  \n");
	printf("\t ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀   \n");
	printf("\n\t                    by michang & sunjo\n");
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
