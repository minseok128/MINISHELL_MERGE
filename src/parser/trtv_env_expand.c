/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv_env_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:03:56 by michang           #+#    #+#             */
/*   Updated: 2024/01/07 18:03:58 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	trtv_dollar_to_value(char *word, char **e_w, t_envs *envsp, int len)
{
	char	*key;
	char	*value;
	int		i;

	key = ft_substr_s(word, 0, len);
	if (!btin_find_node(envsp, key))
	{
		free(key);
		return ;
	}
	value = ft_strdup_s(btin_find_node(envsp, key)->value);
	free(key);
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\"')
			value[i] *= -1;
		i++;
	}
	*e_w = trtv_join_s(*e_w, value);
	return ;
}

static int	trtv_dollar_sign(char *word, char **e_w, t_envs *envsp, int *eno)
{
	int		len;

	len = 0;
	if (ft_isalpha(word[len]) || word[len] == '_')
	{
		while (ft_isalnum(word[len]) || word[len] == '_')
			len++;
	}
	else if (word[len] == '?')
	{
		*e_w = trtv_join_s(*e_w, ft_itoa_s(*eno));
		return (1);
	}
	else
	{
		*(word - 1) *= -1;
		return (-1);
	}
	trtv_dollar_to_value(word, e_w, envsp, len);
	return (len);
}

static void	trtv_env_expand(char *word, char **e_w, t_envs *envsp, int *eno)
{
	int	dquote_flag;
	int	now;
	int	prev;

	prev = 0;
	now = 0;
	dquote_flag = -1;
	while (word[now])
	{
		(word[now] == '\"') && (dquote_flag *= -1);
		if (word[now] == '\'' && dquote_flag == -1)
		{
			now = ft_strchr(&word[now + 1], '\'') - word + 1;
			*e_w = trtv_join_s(*e_w, ft_substr_s(word, prev, now - prev));
		}
		else
		{
			now++;
			if (word[now - 1] == '$')
				now += trtv_dollar_sign(word + now, e_w, envsp, eno);
			else
				*e_w = trtv_join_s(*e_w, ft_substr_s(word, prev, 1));
		}
		prev = now;
	}
}

int	trtv_expansion(t_tr_node *node, t_envs *envsp, int *eno)
{
	char	*e_w;

	e_w = ft_calloc_s(1, sizeof(char));
	trtv_env_expand(node->tk->str, &e_w, envsp, eno);
	free(node->tk->str);
	node->tk->str = e_w;
	node->word_split = ft_calloc_s(sizeof(t_vector), 1);
	vec_init(node->word_split, 1);
	trtv_word_split(node->tk->str, node);
	trtv_quotes_removal(node->word_split);
	trtv_wcard_expand(&(node->word_split));
	return (0);
}
