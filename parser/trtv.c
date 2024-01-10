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

int			trtv_comd_part_travel(t_tr_node *node, t_cmd *cmd);
void		trtv_comd_travel(t_tr_node *node, t_cmd *cmd);
void		trtv_list_travel(t_tr_node *node);
void		trtv_pipe_travel(t_tr_node *node, t_vector *cmds);

int	trtv_comd_part_travel(t_tr_node *node, t_cmd *cmd)
{
	int	i;

	if (node->tk->type == T_WORD)
	{
		i = 0;
		while (i < node->word_split.size)
		{
			if (node->word_split.items[i])
				vec_push_back(&(cmd->argv), node->word_split.items[i]); 
			i++;
		}
	}
	if (node->tk->type == T_REDIR_S_L)
	{

	}
	else if (node->tk->type == T_REDIR_S_R)
	{

	}
	else if (node->tk->type == T_REDIR_D_L)
	{

	}
	else if (node->tk->type == T_REDIR_D_R)
	{

	}
	return (0);
}

void	trtv_comd_travel(t_tr_node *node, t_cmd *cmd)
{
	if (node->left && node->left->bnf_type == TR_COMMAND)
		trtv_comd_travel(node->left, cmd);
	else if (node->left && node->left->bnf_type == TR_COMMAND_PART)
		trtv_comd_part_travel(node->left, cmd);
	if (node->right && node->right->bnf_type == TR_COMMAND_PART)
		trtv_comd_part_travel(node->right, cmd);
}

void	trtv_pipe_travel(t_tr_node *node, t_vector *cmds)
{
	t_cmd		*cmd;

	if (node->left && node->left->bnf_type == TR_LIST)
		trtv_list_travel(node->left);
	else if (node->left && node->left->bnf_type == TR_PIPELINE)
		trtv_pipe_travel(node->left, cmds);
	if (node->left && node->left->bnf_type == TR_COMMAND)
	{
		cmd = ft_calloc_s(sizeof(t_cmd), 1);
		vec_init(&(cmd->argv) ,1);
		trtv_comd_travel(node->left, cmd);
		vec_push_back(&(cmd->argv), 0);
		vec_push_back(cmds, cmd);
	}
	if (node->right && node->right->bnf_type == TR_COMMAND)
	{
		cmd = ft_calloc_s(sizeof(t_cmd), 1);
		vec_init(&(cmd->argv), 1);
		trtv_comd_travel(node->right, cmd);
		vec_push_back(&(cmd->argv), 0);
		vec_push_back(cmds, cmd);
	}
}

void	trtv_list_travel(t_tr_node *node)
{
	t_vector	cmds;

	if (node->left && node->left->bnf_type == TR_LIST)
		trtv_list_travel(node->left);
	vec_init(&cmds, 1);
	if (node->left && node->left->bnf_type == TR_PIPELINE)
	{
		trtv_pipe_travel(node->left, &cmds);
		test_cmds_print(&cmds);
	}
	if (node->right && node->right->bnf_type == TR_PIPELINE)
	{
		trtv_pipe_travel(node->right, &cmds);
		test_cmds_print(&cmds);
	}
}

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
		trtv_quotes_removal(&(node->word_split));
	}
	trtv_expansion_travel(node->left, envsp);
	trtv_expansion_travel(node->right, envsp);
}

void	trtv_start(t_tr_node *root, t_envs *envsp)
{
	trtv_expansion_travel(root, envsp);
	trtv_list_travel(root);
}
