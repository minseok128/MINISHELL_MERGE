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

int	trtv_dollar_sign(char *word, int now, t_envs *envsp)
{
	char	*key;
	int		len;

	len = 0;
	if (ft_isalpha(word[now + len]) || word[now + len] == '_')
	{
		while (ft_isalnum(word[now + len]) || word[now + len] == '_')
			len++;
	}
	key = ft_calloc_s(len + 1, sizeof(char));
	ft_strlcpy(key, &word[now], len + 1);
	printf("key:%s, v:%s\n", key, btin_find_node(envsp, key)->value);
	return (len);
}

void	trtv_command_part(char *word, t_envs *envsp)
{
	int	double_quotes_flag;
	int	now;

	now = 0;
	double_quotes_flag = -1;
	while (word[now])
	{
		if (word[now] == '\"')
			double_quotes_flag *= -1;
		if (word[now] == '\'' && double_quotes_flag == -1)
		{
			now++;
			while (word[now] != '\'')
				now++;
			now++;
		}
		else if (word[now] == '$')
		{
			now++;
			now += trtv_dollar_sign(word, now, envsp);
		}
		else
			now++;
	}
}

void	trtv_env_expand(t_tr_node *node, t_envs *envsp)
{
	if (!node)
		return ;
	if (node->bnf_type == TR_COMMAND_PART)
	{
		trtv_command_part(node->tk->str, envsp);
	}
	trtv_env_expand(node->left, envsp);
	trtv_env_expand(node->right, envsp);
}

void	trtv_traversal(t_tr_node *root, t_envs *envsp)
{
	trtv_env_expand(root, envsp);
}
