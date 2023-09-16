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

t_envp	*ex_find_key(t_envp *head, char *key)
{
	t_envp	*lst;
	int		len;

	len = ft_strlen(key);
	lst = head->next;
	while (lst != NULL)
	{
		//printf("lstval:%s\n", lst->next->value);
		if (ft_strncmp(key, lst->key, len + 1) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	env_print(t_envp *head)
{
	t_envp	*tmp;

	if (head == NULL)
		return ;
	tmp = head->next;
	while (tmp != NULL)
	{
		printf("%s:%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
