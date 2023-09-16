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

t_envp	*find_env(t_envp *head, char *env)
{
	int		i;
	t_envp	*lst;
	t_envp	*pre_lst;

	if (head == NULL)
		return (head);
	pre_lst = head;
	lst = head -> next;
	while (lst -> next != NULL)
	{
		i = 0;
		while (env[i] != '\0' && env[i] != '=' && (lst -> str)[i] != '=')
		{
			if (env[i] != (lst -> str)[i])
				break ;
			i++;
		}
		if ((env[i] == '=' || env[i] == '\0') && (lst -> str)[i] == '=')
			return (pre_lst);
		pre_lst = lst;
		lst = lst -> next;
	}
	return (pre_lst);
}

char	*tk_replace_env_s(char *str, t_envp *head)
{
	int		s;
	int		e;
	int		size;
	char	*res;
	char	tmp[2];
	char	*env_key;
	t_envp	*env;

	res = 0;
	tmp[1] = 0;
	size = ft_strlen(str);
	s = 0;
	while (s < size)
	{
		if (str[s] == '$')
		{
			e = s;
			while (!ft_isspace(str[e]) && str[e] != '\"' && str[e])
				e++;
			env_key = ft_calloc(sizeof(char), e - s + 1);
			if (!env_key)
				exit(1);
			ft_strlcpy(env_key, str + s, e - s + 1);
			env = find_env(head, env_key);
			res = ft_strjoin(res, env->str);
			s = e;
		}
		else
		{
			tmp[0] = str[s];
			res = ft_strjoin(res, tmp);
			s++;
		}
	}
	return (res);
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

void	parse(char *str, t_envp *head)
{
	t_token	*tk;

	str = tk_replace_env_s(str, head);
	tk = tk_split_with_quort_and_space_s(str);
	tk_print(tk);
}
