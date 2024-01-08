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

int	trtv_is_wrap_qoute(char	*word, int now)
{
	return (word[now + 1] && word[now + 2]
		&& (word[now + 1] == '\'' || word[now + 1] == '\"')
		&& word[now] == '$' && word[now + 2] == '$');
}

void	trtv_quotes_removal(t_vector *word_split)
{
	int		i;
	char	*word;
	char	*new_word;
	int		now;
	int		new_now;
	int		in_squote;
	int		in_dquote;

	i = 0;
	while (i < word_split->size)
	{
		word = word_split->items[i];
		new_word = ft_calloc_s(sizeof(char), ft_strlen(word) + 1);
		now = 0;
		new_now = 0;
		in_squote = 0;
		in_dquote = 0;
		while (word[now])
		{
			if (trtv_is_wrap_qoute(word, now))
			{
				new_word[new_now++] = word[++now];
				now++;
			}
			else if (word[now] == '\"' && !in_squote)
				in_dquote = !in_dquote;
			else if (word[now] == '\'' && !in_dquote)
				in_squote = !in_squote;
			else
				new_word[new_now++] = word[now];
			now++;
		}
		free(word);
		word_split->items[i] = new_word;
		i++;
	}
}

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
		printf("[WORD SPLIT] : %s\n", node->tk->str);
		vec_print(&(node->word_split));
		trtv_quotes_removal(&(node->word_split));
		printf("[QUORTES REMOVAL] : %s\n", node->tk->str);
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
