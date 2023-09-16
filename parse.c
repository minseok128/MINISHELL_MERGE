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

t_token	*tk_alloc_s(char *str)
{
	t_token	*tk;

	tk = ft_calloc_s(sizeof(t_token), 1);
	if (str)
		tk->str = str;
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
	start = tk_alloc_s(0);
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
		tmp->str = ft_strdup_s(&str[s]);
		tmp->next = tk_alloc_s(0);
		tmp = tmp->next;
		e++;
		c = 0;
	}
	tk_lstlast_prev(start)->next = 0;
	free(tmp);
	return (start);
}

int	ft_is_meta_char(char *str)
{
	if (str[0] == '|')
		return (T_PIPE);
	if (str[0] == '<' && str[1] == '<')
		return (T_DL_DIREC);
	if (str[0] == '<')
		return (T_SL_DIREC);
	if (str[0] == '>' && str[1] == '>')
		return (T_DR_DIREC);
	if (str[0] == '>')
		return (T_SR_DIREC);
	return (0);
}

char	*tk_str_replace_meta_s(char *str)
{
	int		in_sq;
	int		in_dq;
	int		i;
	int		meta;
	char	*res;
	char	tmp[2];
	
	i = 0;
	res = 0;
	in_dq = 0;
	in_sq = 0;
	tmp[1] = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_sq = !in_sq;
		if (str[i] == '\"')
			in_dq = !in_dq;
		meta = ft_is_meta_char(&str[i]);
		if ((!in_sq || !in_dq) && meta)
		{
			if (meta == T_PIPE)
				res = ft_strjoin_s(res, " | ");
			else if (meta == T_DL_DIREC)
				res = ft_strjoin_s(res, " << ");
			else if (meta == T_SL_DIREC)
				res = ft_strjoin_s(res, " < ");
			else if (meta == T_DR_DIREC)
				res = ft_strjoin_s(res, " >> ");
			else if (meta == T_SR_DIREC)
				res = ft_strjoin_s(res, " > ");
			if (meta == T_DL_DIREC || meta == T_DR_DIREC)
				i++;
		}
		else
		{
			tmp[0] = str[i];
			res = ft_strjoin_s(res, tmp);
		}
		i++;
	}
	free(str);
	return (res);
}

char	*tk_str_replace_env_s(char *str, t_envp *head)
{
	int		in_sq;
	int		s;
	int		e;
	int		size;
	char	*res;
	char	tmp[2];
	char	*env_key;
	t_envp	*env;

	res = 0;
	size = ft_strlen(str);
	s = 0;
	in_sq = 0;
	tmp[1] = 0;
	while (s < size)
	{
		if (str[s] == '\'')
			in_sq = !in_sq;
		if (str[s] == '$' && !in_sq)
		{
			e = s;
			while (!ft_isspace(str[e]) && str[e] != '\"' && str[e])
				e++;
			env_key = ft_calloc_s(sizeof(char), e - s);
			ft_strlcpy(env_key, str + s + 1, e - s);
			env = ex_find_key(head, env_key);
			printf("env:%p\n", env);
			if (env)
				res = ft_strjoin_s(res, env->value);
			s = e;
		}
		else
		{
			tmp[0] = str[s];
			res = ft_strjoin_s(res, tmp);
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

	str = tk_str_replace_meta_s(str);
	str = tk_str_replace_env_s(str, head);
	tk = tk_split_with_quort_and_space_s(str);
	//tk_split_with_direct_pipe(tk);
	tk_print(tk);
}
