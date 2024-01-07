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

char	*trtv_join_s(char *s1, char *s2)
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

int	trtv_dollar_sign(char *word, int now, char **e_w, t_envs *envsp)
{
	char	*key;
	t_envs	*finded;
	char	*value;
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
	value = trtv_join_s(ft_strdup_s("$"), ft_strdup_s(finded->value));
	*e_w = trtv_join_s(*e_w, trtv_join_s(value, ft_strdup_s("$")));
	return (len);
}

void	trtv_command_part(char *word, char **e_w, t_envs *envsp)
{
	int		dquote_flag;
	int		now;
	int		prev;

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
		else if (word[now] == '$')
		{
			now++;
			now += trtv_dollar_sign(word, now, e_w, envsp);
		}
		else
		{
			now++;
			*e_w = trtv_join_s(*e_w, ft_substr_s(word, prev, 1));
		}
		prev = now;
	}
}

void	trtv_env_expand(t_tr_node *node, t_envs *envsp)
{
	char	*e_w;

	if (!node)
		return ;
	if (node->bnf_type == TR_COMMAND_PART)
	{
		e_w = ft_calloc_s(1, sizeof(char));
		trtv_command_part(node->tk->str, &e_w, envsp);
		free(node->tk->str);
		node->tk->str = e_w;
	}
	trtv_env_expand(node->left, envsp);
	trtv_env_expand(node->right, envsp);
}

void	trtv_traversal(t_tr_node *root, t_envs *envsp)
{
	trtv_env_expand(root, envsp);
	test_tr_print_tree(root, "$ EXPANSION");
}
