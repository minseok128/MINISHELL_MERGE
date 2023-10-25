/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:01 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 22:39:01 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_free_two(char *str1, char *str2)
{
	free(str1);
	free(str2);
}

int	bi_first_character_check(char c)
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

t_envp	*bi_find_key(t_envp *head, char *key)
{
	t_envp	*lst;
	int		len;

	len = ft_strlen(key);
	lst = head->next;
	while (lst != NULL)
	{
		if (ft_strncmp(key, lst->key, len + 1) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	bi_add_env(t_envp *head, char **key_and_value)
{
	t_envp	*lst;
	t_envp	*next;
	t_envp	*find;

	lst = head;
	next = lst->next;
	find = bi_find_key(head, key_and_value[0]);
	if (next == NULL)
		lst->next = bi_make_list(key_and_value);
	else if (find == NULL)
	{
		while (next->next != NULL)
		{
			lst = next;
			next = next->next;
		}
		lst->next = bi_make_list(key_and_value);
		lst->next->next = next;
	}
	else
	{
		bi_free_two(find->value, key_and_value[0]);
		find->value = key_and_value[1];
	}
}

void	bi_export(t_envp *head, char *input)
{
	int		i;
	char	**arr;
	char	**key_and_value;

	arr = ft_split(input, ' ');
	i = 0;
	while (arr[i] != NULL)
	{
		key_and_value = bi_divide_key_and_value(arr[i]);
		free(arr[i]);
		if (key_and_value != NULL)
		{
			if (bi_first_character_check(key_and_value[0][0]) == 1)
				bi_add_env(head, key_and_value);
			else
			{
				printf("bash: export: '%s': not a valid identifier\n", arr[i]);
				errno = 1;
			}
			free(key_and_value);
		}
		i++;
	}
	free(arr);
}
