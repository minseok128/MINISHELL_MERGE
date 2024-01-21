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

static int	trtv_dollar_sign(char *word, int now, char **e_w, t_envs *envsp)
{
	char	*key;
	char	*value;
	int		len;
	int		i;

	len = 0;
	if (ft_isalpha(word[now + len]) || word[now + len] == '_')
	{
		while (ft_isalnum(word[now + len]) || word[now + len] == '_')
			len++;
	}
	else if (word[now + len] == '?')
	{
		*e_w = trtv_join_s(*e_w, ft_itoa_s(g_errno));
		return (1);
	}
	else
	{
		word[now - 1] *= -1;
		return (-1);
	}
	key = ft_substr_s(word, now, len);
	if (!btin_find_node(envsp, key))
	{
		free(key);
		return (len); 
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

int	trtv_expansion_travel(t_tr_node *node, t_envs *envsp)
{
	char	*e_w;

	if (!node)
		return (0);
	if (node->bnf_type == TR_COMMAND_PART)
	{
		e_w = ft_calloc_s(1, sizeof(char));
		trtv_env_cmdp(node->tk->str, &e_w, envsp);
		free(node->tk->str);
		node->tk->str = e_w;
		vec_init(&(node->word_split), 1);
		trtv_word_split(node->tk->str, node);
		trtv_quotes_removal(&(node->word_split));
	}
	trtv_expansion_travel(node->left, envsp);
	trtv_expansion_travel(node->right, envsp);
	return (0);
}
