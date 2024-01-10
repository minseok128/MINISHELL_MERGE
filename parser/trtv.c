/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:37:45 by michang           #+#    #+#             */
/*   Updated: 2024/01/04 20:37:46 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// void	trtv_comd_part_travel(t_tr_node *node)
// {
// 	if (node->tk->type == T_WORD)
// 	{

// 	}
// 	else
// 	{

// 	}
// }

// void	trtv_comd_travel(t_tr_node *node)
// {
// 	if (node->left && node->left->bnf_type == TR_COMMAND)
// 		trtv_comd_travel(node->left);
// 	else if (node->left && node->left->bnf_type == TR_COMMAND_PART)
// 		trtv_comd_part_travel(node->left);
// 	if (node->right && node->right->bnf_type == TR_COMMAND_PART)
// 		trtv_comd_part_travel(node->right);
// }

// void	trtv_pipe_travel(t_tr_node *node, t_vector *argv)
// {
// 	// t_vector	*

// 	if (node->left && node->left->bnf_type == TR_LIST)
// 		trtv_list_travel(node->left);
// 	else if (node->left && node->left->bnf_type == TR_PIPELINE)
// 		trtv_pipe_travel(node->left, argv);
// 	else

// 	else
// 	{

// 	}
// }

// void	trtv_list_travel(t_tr_node *node)
// {
// 	if (node->left && node->left->bnf_type == TR_PIPELINE)
// 	{

// 	}
// 	else
// 		trtv_list_travel(node->left);
// 	if (node->right && node->right->bnf_type == TR_PIPELINE)
// 	{

// 	}
// }

void	trtv_expansion_travel(t_tr_node *node, t_envs *envsp)
{
	char	*e_w;

	if (!node)
		return ;
	if (node->bnf_type == TR_COMMAND_PART)
	{
		e_w = ft_calloc_s(1, sizeof(char));
		trtv_env_cmdp(node->tk->str, &e_w, envsp);
		free(node->tk->str);
		node->tk->str = e_w;
		vec_init(&(node->word_split), 1);
		trtv_word_split(node->tk->str, node);
		// printf("[WORD SPLIT] : %s\n", node->tk->str);
		// vec_print(&(node->word_split));
		trtv_quotes_removal(&(node->word_split));
		// printf("[QUORTES REMOVAL] : %s\n", node->tk->str);
		// vec_print(&(node->word_split));
	}
	trtv_expansion_travel(node->left, envsp);
	trtv_expansion_travel(node->right, envsp);
}

void	trtv_start(t_tr_node *root, t_envs *envsp)
{
	trtv_expansion_travel(root, envsp);
	test_tr_print_tree(root, "$ EXPANSION");
}
