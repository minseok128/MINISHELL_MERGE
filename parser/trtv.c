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

char	*trtv_make_new_word_without_quotes(char *word)
{
	int		now;
	char	*new_word;
	int		new_now;
	int		in_squote;
	int		in_dquote;

	new_word = ft_calloc_s(sizeof(char), ft_strlen(word) + 1);
	now = 0;
	new_now = 0;
	in_squote = 0;
	in_dquote = 0;
	while (word[now])
	{
		if (word[now] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (word[now] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else
			new_word[new_now++] = word[now];
		now++;
	}
	free(word);
	return (new_word);
}

void	trtv_quotes_removal(t_vector *word_split)
{
	int		i;
	char	*new_word;

	i = 0;
	while (i < word_split->size)
	{
		new_word = trtv_make_new_word_without_quotes(word_split->items[i]);
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
		else if (word[now + len] == '\'' || word[now + len] == '\"')
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
