/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:01:54 by michang           #+#    #+#             */
/*   Updated: 2023/09/15 17:01:56 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tk_lstlast_prev(t_token *lst)
{
	if (!lst)
		return (0);
	if (!(lst->next))
		return (0);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}

t_token	*tk_lstlast(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	tk_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	last = tk_lstlast(*lst);
	if (last)
		last->next = new;
	else
		*lst = new;
}

void	tk_lstadd_front(t_token **lst, t_token *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	tk_add_s(t_token *prev, t_token *new)
{
	t_token	*tmp;

	tmp = prev->next;
	prev->next = new;
	if (!new)
		new->next = tmp;
}

int	ft_isspace(char	c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

t_token	*tk_alloc_s(t_token_type type, char *str)
{
	t_token	*tk;

	tk = ft_calloc_s(sizeof(t_token), 1);
	if (str)
		tk->str = str;
	tk->type = type;
	return (tk);
}

void	tk_print(t_token *tk)
{
	while (tk)
	{
		printf("%s[%d]", tk->str, tk->type);
		tk = tk->next;
		if (tk)
			printf(" ==> ");
	}
	printf("\n");
}

int	tk_is_meta_char(char *str)
{
	if (str[0] == '\0')
		return (0);
	else if (str[0] == '(')
		return (T_PARENT_L);
	else if (str[0] == ')')
		return (T_PARENT_R);
	else if (str[0] == '&' && str[1] == '&')
		return (T_AND);
	else if (str[0] == '|' && str[1] == '|')
		return (T_OR);
	else if (str[0] == '|')
		return (T_PIPE);
	else if (str[0] == '<' && str[1] == '<')
		return (T_REDIR_D_L);
	else if (str[0] == '<')
		return (T_REDIR_S_L);
	else if (str[0] == '>' && str[1] == '>')
		return (T_REDIR_D_R);
	else if (str[0] == '>')
		return (T_REDIR_S_R);
	return (0);
}

void	tk_quotes(char *str, t_token **tk_head, int now)
{
	t_token	*new_tk;
	char	*new_str;
	int		len;

	len = 1;
	while (str[now + len] && str[now + len] != str[now])
		len++;
	new_str = (char *)ft_calloc_s(1, len + 1);
	ft_strlcpy(new_str, &str[now], len + 1);
	new_tk = tk_alloc_s(T_WORD, new_str);
	tk_lstadd_back(tk_head, new_tk);
}

void	tk_meta(char *str, t_token **tk_head, int now)
{
	t_token			*new_tk;
	t_token_type	new_type;
	char			*new_str;
	int				len;

	
	new_type = tk_is_meta_char(str);
	len = 1;
	if (new_type == T_AND || new_type == T_OR
		|| new_type == T_REDIR_D_L || new_type == T_REDIR_D_R)
		len++;
	new_str = (char *)ft_calloc_s(1, len + 1);
	ft_strlcpy(new_str, &str[now], len + 1);
	new_tk = tk_alloc_s(new_type, new_str);
	tk_lstadd_back(tk_head, new_tk);
}

void	tk_word(char *str, t_token **tk_head, int now)
{
	t_token	*new_tk;
	char	*new_str;
	int		len;

	len = 0;
	while (tk_is_meta_char(&str[now + len]) && ft_isspace(str[now + len]))
		len++;
	new_str = (char *)ft_calloc_s(1, len + 1);
	ft_strlcpy(new_str, &str[now], len + 1);
	new_tk = tk_alloc_s(T_WORD, new_str);
	tk_lstadd_back(tk_head, new_tk);
}

void	tk_default(char *str, t_token **tk_head)
{
	int	now;
	
	now = 0;
	while (str[now])
	{
		if (tk_is_meta_char(str))
			tk_meta(str, tk_head, now);
		else if (str[now] == '\'' || str[now] == '\"')
			tk_quotes(str, tk_head, now);
		else if (str[now] && ft_isspace(str[now]))
			tk_word(str, tk_head, now);
		else
			now++;
	}
	return ;
}

void	tk_tokenize(char *str)
{
	t_token	*tk_head;

	tk_default(str, &tk_head);
	tk_print(tk_head);
}
