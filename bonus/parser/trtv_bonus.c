/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:37:45 by michang           #+#    #+#             */
/*   Updated: 2024/01/21 18:58:15 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	trtv_comd_part_travel(t_tr_node *node, t_cmds *cmd, t_envs *envsp)
{
	int	i;
	int	fail_flag;

	fail_flag = 0;
	if (node->tk->type == T_WORD)
	{
		trtv_expansion(node, envsp);
		i = 0;
		while (i < node->word_split->size)
		{
			if (node->word_split->items[i])
				vec_push_back(&(cmd->argv), node->word_split->items[i]);
			i++;
		}
	}
	if (node->tk->type == T_REDIR_S_L)
		fail_flag = trtv_redir_s_l(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_S_R)
		fail_flag = trtv_redir_s_r(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_D_L)
		fail_flag = trtv_redir_d_l(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_D_R)
		fail_flag = trtv_redir_d_r(cmd, node->tk->str);
	return (fail_flag);
}

int	trtv_comd_travel(t_tr_node *node, t_cmds *cmd, t_envs *envsp)
{
	if (node->left && node->left->bnf_type == TR_COMMAND)
	{
		if (trtv_comd_travel(node->left, cmd, envsp))
			return (1);
	}
	else if (node->left && node->left->bnf_type == TR_COMMAND_PART)
	{
		if (trtv_comd_part_travel(node->left, cmd, envsp))
			return (1);
	}
	if (node->right && node->right->bnf_type == TR_COMMAND_PART)
	{
		if (trtv_comd_part_travel(node->right, cmd, envsp))
			return (1);
	}
	return (0);
}

int	trtv_pipe_travel(t_tr_node *node, t_cmds *cmds_h, t_envs *envsp)
{
	t_cmds		*cmd;

	if (node->left && node->left->bnf_type == TR_LIST)
	{
		trtv_list_travel(node->left, envsp);
		return (1);
	}
	else if (node->left && node->left->bnf_type == TR_PIPELINE)
		trtv_pipe_travel(node->left, cmds_h, envsp);
	if (node->left && node->left->bnf_type == TR_COMMAND)
	{
		cmd = ex_cmdsp_add_back(cmds_h);
		vec_init(&(cmd->argv), 1);
		trtv_comd_travel(node->left, cmd, envsp);
		vec_push_back(&(cmd->argv), 0);
	}
	if (node->right && node->right->bnf_type == TR_COMMAND)
	{
		cmd = ex_cmdsp_add_back(cmds_h);
		vec_init(&(cmd->argv), 1);
		trtv_comd_travel(node->right, cmd, envsp);
		vec_push_back(&(cmd->argv), 0);
	}
	return (0);
}

void	trtv_list_child(t_tr_node *child, t_envs *envsp)
{
	t_cmds	*cmds_h;

	cmds_h = ex_cmdsp_init();
	if (child && child->bnf_type == TR_PIPELINE)
	{
		if (!trtv_pipe_travel(child, cmds_h, envsp))
			ex_cmd_loop(cmds_h, envsp);
		else
			free(cmds_h);
	}
}

int	trtv_list_travel(t_tr_node *node, t_envs *envsp)
{
	if (node->left && node->left->bnf_type == TR_LIST)
	{
		if (!trtv_list_travel(node->left, envsp))
			trtv_list_child(node->right, envsp);
	}
	else
		trtv_list_child(node->left, envsp);
	return (node->tk
		&& ((!g_errno && node->tk->type != T_AND)
			|| (g_errno && node->tk->type == T_AND)));
}
