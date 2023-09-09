/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:13:54 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/09 10:38:44 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_export(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
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

void	add_env(t_envp *head, char *env)
{
	t_envp	*lst;
	t_envp	*pre_lst;

	pre_lst = find_env(head, env);
	lst = pre_lst -> next;
	if (lst == NULL || lst -> next == NULL)
	{
		pre_lst -> next = make_lst(env);
		pre_lst -> next -> next = lst;
	}
	else
	{
		free(lst -> str);
		lst -> str = env;
	}
}

void	ft_export(t_envp *head, char *input)
{
	int		i;
	char	**arr;

	arr = ft_split(input, ' ');
	i = 0;
	while (arr[i] != NULL)
	{
		if (can_export(arr[i][0]))
		{
			if (find_equal(arr[i]))
				add_env(head, arr[i]);
			else
				free(arr[i]);
		}
		else
		{
			printf("bash: export: '%s': not a valid identifier\n", arr[i]);
			errno = 1;
			free(arr[i]);
		}
		i++;
	}
	free(arr);
}
