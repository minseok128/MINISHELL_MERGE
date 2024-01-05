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
#include "../btin/btin.h"


int	trtv_dollar_sign(char *word, int now)
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
	printf("key:%s\n", key);
	return (len);
}

void	trtv_command_part(char *word)
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
			now += trtv_dollar_sign(word, now);
		}
		else
			now++;
	}
}

void	trtv_env_expand(t_tr_node *node)
{
	if (!node)
		return ;
	if (node->bnf_type == TR_COMMAND_PART)
	{
		// test_print_command_part(node);
		trtv_command_part(node->tk->str);
	}
	trtv_env_expand(node->left);
	trtv_env_expand(node->right);
}

void	trtv_traversal(t_tr_node *root)
{
	trtv_env_expand(root);
}
