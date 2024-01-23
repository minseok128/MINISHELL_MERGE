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

#include "../minishell.h"

static int	tk_meta(char *str, t_token **tk_head, int now)
{
	t_token_type	new_type;
	char			*new_str;
	int				len;

	new_type = tk_is_meta_char(&str[now]);
	len = 1;
	if (new_type == T_AND || new_type == T_OR
		|| new_type == T_REDIR_D_L || new_type == T_REDIR_D_R)
		len++;
	new_str = (char *)ft_calloc_s(len + 1, sizeof(char));
	ft_strlcpy(new_str, &str[now], len + 1);
	tk_lstadd_back(tk_head, tk_alloc_s(new_type, new_str));
	return (len);
}

static int	tk_word(char *str, t_token **tk_head, int now, char *is_error)
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
				*is_error = quotes;
		}
		else
			len++;
	}
	new_str = (char *)ft_calloc_s(len + 1, sizeof(char));
	ft_strlcpy(new_str, &str[now], len + 1);
	tk_lstadd_back(tk_head, tk_alloc_s(T_WORD, new_str));
	return (len);
}

int	tk_tokenize(char *str, t_token **tk_head)
{
	t_token	*tk_last;
	int		now;
	char	is_error;

	is_error = 0;
	now = 0;
	while (str[now])
	{
		if (tk_is_meta_char(&str[now]) != 0)
			now += tk_meta(str, tk_head, now);
		else if (!ft_isspace(str[now]))
			now += tk_word(str, tk_head, now, &is_error);
		else
			now++;
	}
	tk_last = tk_lstlast(*tk_head);
	tk_last->next = tk_alloc_s(T_NEWLINE, ft_strdup_s("newline"));
	if (is_error)
	{
		printf("minishell: unexpected newline ");
		printf("while looking for matching `%c\'\n", is_error);
		return (mktr_print_unexpected("newline"));
	}
	else
		return (0);
		// return (tk_print(*tk_head));
}
