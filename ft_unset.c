/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:00:04 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/09 15:19:00 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(t_envp *head, char *env)
{
	t_envp	*pre_lst;
	t_envp	*lst;

	pre_lst = find_env(head, env);
	lst = pre_lst -> next;
	if (lst != NULL && lst -> next != NULL)
	{
		pre_lst -> next = lst -> next;
		free(lst -> str);
		free(lst);
	}
}

void	ft_unset(t_envp *head, char *input)
{
	int		i;
	char	**arr;

	arr = ft_split(input, ' ');
	i = 0;
	while (arr[i] != NULL)
	{
		if (can_export(arr[i][0]))
			remove_env(head, arr[i]);
		else
		{
			printf("bash: unset: '%s': not a valid identifier\n", arr[i]);
			errno = 1;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
}
