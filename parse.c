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

int	ft_isspace(char	c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

t_token	*tk_alloc_s(void)
{
	t_token	*tk;

	tk = ft_calloc(sizeof(t_token), 1);
	if (!tk)
		exit(1);
	return (tk);
}

t_token	*tk_split_with_quort_and_space_s(char *str){
	t_token *start;
	t_token *tmp;
	int		size;
	int		s;
	int		e;
	char	c;

	size = ft_strlen(str);
	start = tk_alloc_s();
	tmp = start;
	s = 0;
	e = 0;
	c = 0;
	while (e < size)
	{
		while (ft_isspace(str[e]) && str[e])
			e++;
		if (!str[e])
			break ;
		s = e;
		while (!ft_isspace(str[e]) && str[e])
		{
			if (str[e] == '\'' || str[e] == '\"')
			{
				c = str[e++];
				while (str[e] != c && str[e])
					e++;
			}
			e++;
		}
		str[e] = 0;
		tmp->str = ft_strdup(&str[s]);
		tmp->next = tk_alloc_s();
		tmp = tmp->next;
		e++;
		c = 0;
	}
	tk_lstlast_prev(start)->next = 0;
	free(tmp);
	return (start);
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

void	parse(char *str)
{
	t_token	*tk;

	tk = tk_split_with_quort_and_space_s(str);
	tk_print(tk);
}
