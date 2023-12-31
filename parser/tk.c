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

#include "tk.h"

int	tk_quotes(char *str, t_token **tk_head, int now)
{
	t_token	*new_tk;
	char	*new_str;
	int		len;

	len = 1;
	while (str[now + len] && str[now + len] != str[now])
		len++;
	if (str[now + len])
		len++;
	new_str = (char *)ft_calloc_s(len + 1, sizeof(char));
	ft_strlcpy(new_str, &str[now], len + 1);
	new_tk = tk_alloc_s(T_WORD, new_str);
	tk_lstadd_back(tk_head, new_tk);
	return (len);
}

int	tk_meta(char *str, t_token **tk_head, int now)
{
	t_token			*new_tk;
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
	new_tk = tk_alloc_s(new_type, new_str);
	tk_lstadd_back(tk_head, new_tk);
	return (len);
}

int	tk_word(char *str, t_token **tk_head, int now)
{
	t_token	*new_tk;
	char	*new_str;
	int		len;

	len = 0;
	while (str[now + len] && !tk_is_meta_char(&str[now + len])
		&& !ft_isspace(str[now + len]))
		len++;
	new_str = (char *)ft_calloc_s(len + 1, sizeof(char));
	ft_strlcpy(new_str, &str[now], len + 1);
	new_tk = tk_alloc_s(T_WORD, new_str);
	tk_lstadd_back(tk_head, new_tk);
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
		else if (str[now] == '\'' || str[now] == '\"')
			now += tk_quotes(str, &tk_head, now);
		else if (str[now] && !ft_isspace(str[now]))
			now += tk_word(str, &tk_head, now);
		else
			now++;
	}
	tk_lstlast(tk_head)->next = 0;
	tk_print(tk_head);
}
