/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:01:54 by michang           #+#    #+#             */
/*   Updated: 2023/09/15 17:01:56 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	tk_meta(char *str, t_vector *tokens, int now)
{
	t_token_type	new_type;
	char			*new_str;
	int				len;

	new_type = tk_is_meta_char(&str[now]);
	len = 1;
	if (new_type == T_AND || new_type == T_OR
		|| new_type == T_REDIR_D_L || new_type == T_REDIR_D_R)
		len++;
	vec_push_back(tokens, tk_alloc_s(new_type, ft_substr_s(str, now, len)));
	return (len);
}

static int	tk_word(char *str, t_vector *tokens, int now, int *is_error)
{
	char	*new_str;
	int		len;
	char	quotes;

	len = 0;
	while (str[now + len] && !tk_is_meta_char(&str[now + len])
		&& !ft_isspace(str[now + len]))
	{
		if (str[now + len] == '\'' || str[now + len] == '\"')
		{
			quotes = str[now + len++];
			while (str[now + len] && str[now + len] != quotes)
				len++;
			if (str[now + len])
				len++;
			else
				*is_error = 1;
		}
		else
			len++;
	}
	vec_push_back(tokens, tk_alloc_s(T_WORD, ft_substr_s(str, now, len)));
	return (len);
}

int	tk_tokenize(char *str, t_vector *tokens)
{
	int		now;
	int		is_error;

	vec_init(tokens, 1);
	is_error = 0;
	now = 0;
	while (str[now])
	{
		if (tk_is_meta_char(&str[now]) != 0)
			now += tk_meta(str, tokens, now);
		else if (!ft_isspace(str[now]))
			now += tk_word(str, tokens, now, &is_error);
		else
			now++;
	}
	vec_push_back(tokens, tk_alloc_s(T_NEWLINE, ft_strdup_s("newline")));
	if (is_error)
		return (mktr_print_unexpected("newline"));
	else
		return (tk_print(tokens));
}
