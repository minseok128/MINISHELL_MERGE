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

void	trtv_word_split(char *word, t_tr_node *node)
{
	unsigned int		now;
	unsigned int		len;
	char				quotes;

	now = 0;
	len = 0;
	while (now + len <= ft_strlen(word))
	{
		if (ft_isspace(word[now + len]) || !word[now + len])
		{
			vec_push_back(&(node->word_split), ft_substr_s(word, now, len));
			now += len;
			while (ft_isspace(word[now]))
				now++;
			if (!word[now])
				now++;
			len = -1;
		}
		else if ((word[now + len] == '\'' || word[now + len] == '\"')
			&& (now + len == 0 || !(word[now + len - 1] == '$'
					&& word[now + len + 1] == '$')))
		{
			quotes = word[now + len++];
			while (word[now + len] != quotes)
				len++;
		}
		len++;
	}
}

void	trtv_traversal(t_tr_node *node, t_envs *envsp)
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
		vec_print(&(node->word_split));
	}
	trtv_traversal(node->left, envsp);
	trtv_traversal(node->right, envsp);
}

void	trtv_start(t_tr_node *root, t_envs *envsp)
{
	trtv_traversal(root, envsp);
	test_tr_print_tree(root, "$ EXPANSION");
}
