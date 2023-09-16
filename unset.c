/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:19 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/16 16:26:27 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	un_remove_env(t_envp *head, char *key)
{
	t_envp	*lst;
	t_envp	*next;
	t_envp	*find;

	lst = head;
	next = lst->next;
	find = ex_find_key(head, key);
	if (find != NULL)
	{
		while (next != find)
		{
			lst = next;
			next = next->next;
		}
		lst->next = next->next;
		free(next->key);
		free(next->value);
		free(next);
	}
}

void	un_unset(t_envp *head, char *input)
{
	int		i;
	char	**arr;

	arr = ft_split(input, ' ');
	i = 0;
	while (arr[i] != NULL)
	{
		if (ex_first_character_check(arr[i][0]) == 1)
			un_remove_env(head, arr[i]);
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
