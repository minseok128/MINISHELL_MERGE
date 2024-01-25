/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv_word_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:03:56 by michang           #+#    #+#             */
/*   Updated: 2024/01/07 18:03:58 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*trtv_make_new_word_without_quotes(char *word)
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
		{
			(!(in_dquote || in_squote) && word[now] == '*') && (word[now] = 6);
			new_word[new_now++] = word[now];
		}
		now++;
	}
	return (new_word);
}

void	trtv_quotes_removal(t_vector *word_split)
{
	int		i;
	int		now;
	char	*new_word;

	i = 0;
	while (i < word_split->size)
	{
		now = 0;
		if (*(char *)(word_split->items[i]) == '\0')
			new_word = 0;
		else
			new_word = trtv_make_new_word_without_quotes(word_split->items[i]);
		free(word_split->items[i]);
		while (new_word && new_word[now])
		{
			if (new_word[now] < 0)
				new_word[now] *= -1;
			now++;
		}
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
			vec_push_back(node->word_split, ft_substr_s(word, now, len));
			now += len;
			while (ft_isspace(word[now]))
				now++;
			(!word[now]) && (now++);
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
