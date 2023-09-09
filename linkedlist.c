/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:40:26 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/08 23:05:47 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*make_lst(char *src)
{
	t_envp	*lst;
	char	*s;

	lst = malloc(sizeof(t_envp));
	if (lst == NULL)
		error_and_exit();
	s = ft_strdup(src);
	if (s == NULL)
		error_and_exit();
	lst -> str = s;
	lst -> next = NULL;
	return (lst);
}

t_envp	*make_linkedlist(char **envp)
{
	int		i;
	t_envp	*head;
	t_envp	*ptr;

	head = make_lst("head");
	ptr = head;
	i = 0;
	while (envp[i] != NULL)
	{
		ptr -> next = make_lst(envp[i]);
		ptr = ptr -> next;
		i++;
	}
	return (head);
}
