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

static void	tk_print(t_token *tk)
{
	printf("\n[TOKEN] DONE!\n");
	while (tk)
	{
		printf("%s[%d]", tk->str, tk->type);
		tk = tk->next;
		if (tk)
			printf(" ==> ");
	}
	printf("\n");
}

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

static int	tk_word(char *str, t_token **tk_head, int now)
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
		}
		else
			len++;
	}
	new_str = (char *)ft_calloc_s(len + 1, sizeof(char));
	ft_strlcpy(new_str, &str[now], len + 1);
	tk_lstadd_back(tk_head, tk_alloc_s(T_WORD, new_str));
	return (len);
}

void	tk_tokenize(char *str)
{
	t_token	*tk_head;
	int		now;

	tk_head = 0;
	now = 0;
	while (str[now])
	{
		if (tk_is_meta_char(&str[now]) != 0)
			now += tk_meta(str, &tk_head, now);
		else if (!ft_isspace(str[now]))
			now += tk_word(str, &tk_head, now);
		else
			now++;
	}
	tk_lstlast(tk_head)->next = tk_alloc_s(T_NEWLINE, "newline");
	tk_print(tk_head);
	mktr_make_tree(tk_head);
}
