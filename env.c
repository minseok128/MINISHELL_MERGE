/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:39:15 by michang           #+#    #+#             */
/*   Updated: 2023/09/16 11:39:16 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*env_alloc_s(char *str)
{
	t_envp	*lst;

	lst = ft_calloc(sizeof(t_envp), 1);
	if (lst == NULL)
		exit(1);
	lst->str = ft_strdup(str);
	if (lst->str == NULL)
		exit(1);
	return (lst);
}

t_envp	*env_init_list_s(char **envp)
{
	int		i;
	t_envp	*head;
	t_envp	*tmp;

	head = env_alloc_s("head");
	tmp = head;
	i = 0;
	while (envp[i] != NULL)
	{
		tmp->next = env_alloc_s(envp[i]);
		tmp = tmp->next;
		i++;
	}
	return (head);
}

void	env_print(t_envp *head)
{
	t_envp	*tmp;

	if (head == NULL)
		return ;
	tmp = head->next;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}
