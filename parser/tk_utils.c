/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:01:54 by michang           #+#    #+#             */
/*   Updated: 2023/09/15 17:01:56 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tk.h"

t_token	*tk_lstlast(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	tk_lstadd_back(t_token **lst, t_token *new_token)
{
	t_token	*last;

	if (!new_token)
		return ;
	last = tk_lstlast(*lst);
	if (last)
		last->next = new_token;
	else
		*lst = new_token;
}

int	ft_isspace(char c)
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

t_token_type	tk_is_meta_char(char *str)
{
	if (!str[0])
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
