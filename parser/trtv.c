/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 20:37:45 by michang           #+#    #+#             */
/*   Updated: 2024/01/18 17:12:06 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trtv_comd_part_travel(t_tr_node *node, t_cmds *cmd)
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
		trtv_redir_s_l(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_S_R)
		trtv_redir_s_r(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_D_L)
		trtv_redir_d_l(cmd, node->tk->str);
	else if (node->tk->type == T_REDIR_D_R)
		trtv_redir_d_r(cmd, node->tk->str);
	return (0);
}

void	trtv_comd_travel(t_tr_node *node, t_cmds *cmd)
{
	if (node->left && node->left->bnf_type == TR_COMMAND)
		trtv_comd_travel(node->left, cmd);
	else if (node->left && node->left->bnf_type == TR_COMMAND_PART)
		trtv_comd_part_travel(node->left, cmd);
	if (node->right && node->right->bnf_type == TR_COMMAND_PART)
		trtv_comd_part_travel(node->right, cmd);
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
		trtv_comd_travel(node->left, cmd);
		vec_push_back(&(cmd->argv), 0);
	}
	if (node->right && node->right->bnf_type == TR_COMMAND)
	{
		cmd = ex_cmdsp_add_back(cmds_h);
		vec_init(&(cmd->argv), 1);
		trtv_comd_travel(node->right, cmd);
		vec_push_back(&(cmd->argv), 0);
	}
	return (0);
}

int	trtv_list_travel(t_tr_node *node, t_envs *envsp)
{
	t_cmds	*cmds_h;

	if (node->left && node->left->bnf_type == TR_LIST)
	{
		if (!trtv_list_travel(node->left, envsp))
		{
			cmds_h = ex_cmdsp_init();
			if (node->right && node->right->bnf_type == TR_PIPELINE)
				if (!trtv_pipe_travel(node->right, cmds_h, envsp))
					ex_cmd_loop(cmds_h, envsp);
		}
	}
	else
	{
		cmds_h = ex_cmdsp_init();
		if (node->left && node->left->bnf_type == TR_PIPELINE)
			if (!trtv_pipe_travel(node->left, cmds_h, envsp))
				ex_cmd_loop(cmds_h, envsp);
	}
	return (node->tk
		&& ((g_errno && node->tk->type == T_OR)
			|| (!g_errno && node->tk->type == T_OR)));
}
