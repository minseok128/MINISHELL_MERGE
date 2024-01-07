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

#include "parser.h"

static char	*trtv_join_s(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!new)
		exit(1);
	ft_strlcpy(new, s1, s1_len + 1);
	ft_strlcat(new + s1_len, s2, s1_len + s2_len + 1);
	free(s1);
	free(s2);
	return (new);
}

static char	*trtv_wrap_quotes(char *word)
{
	char	*new_word;
	int		now;
	int		len;

	now = 0;
	len = 0;
	while (word[now])
	{
		if (word[now] == '\'' || word[now] == '\"')
			len++;
		now++;
	}
	len += now;
	new_word = ft_calloc_s(sizeof(char), len);
	now = 0;
	len = 0;
	while (word[now])
	{
		if (word[now] == '\'' || word[now] == '\"')	
		{
			new_word[len++] = '$';
			new_word[len++] = word[now++];
			new_word[len++] = '$';
		}
		else
			new_word[len++] = word[now++];
	}
	return (new_word);
}

static int	trtv_dollar_sign(char *word, int now, char **e_w, t_envs *envsp)
{
	char	*key;
	t_envs	*finded;
	int		len;

	len = 0;
	if (ft_isalpha(word[now + len]) || word[now + len] == '_')
	{
		while (ft_isalnum(word[now + len]) || word[now + len] == '_')
			len++;
	}
	key = ft_calloc_s(len + 1, sizeof(char));
	ft_strlcpy(key, &word[now], len + 1);
	finded = btin_find_node(envsp, key);
	if (!finded)
		return (len);
	*e_w = trtv_join_s(*e_w, trtv_wrap_quotes(finded->value));
	return (len);
}

void	trtv_env_cmdp(char *word, char **e_w, t_envs *envsp)
{
	int	dquote_flag;
	int	now;
	int	prev;

	prev = 0;
	now = 0;
	dquote_flag = -1;
	while (word[now])
	{
		if (word[now] == '\"')
			dquote_flag *= -1;
		if (word[now] == '\'' && dquote_flag == -1)
		{
			now = ft_strchr(&word[now + 1], '\'') - word + 1;
			*e_w = trtv_join_s(*e_w, ft_substr_s(word, prev, now - prev));
		}
		else
		{
			now++;
			if (word[now - 1] == '$')
				now += trtv_dollar_sign(word, now, e_w, envsp);
			else
				*e_w = trtv_join_s(*e_w, ft_substr_s(word, prev, 1));
		}
		prev = now;
	}
}
