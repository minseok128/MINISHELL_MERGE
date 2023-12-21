/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:01 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/21 21:15:38 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_character_check(char c)
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

t_envp	*find_node(t_envp *envp_head, char *key)
{
	t_envp	*node;
	int		key_len;

	key_len = ft_strlen(key);
	node = envp_head->next;
	while (node != NULL)
	{
		if (ft_strncmp(key, node->key, key_len + 1) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	add_new_node(t_envp *now, char **key_and_value)
{
	t_envp	*next;

	if (now == NULL)
		now->next = make_env_node(key_and_value);
	else
	{
		next = now->next;
		while (next->next != NULL)
		{
			now = next;
			next = next->next;
		}
		now->next = make_env_node(key_and_value);
		now->next->next = next;
	}
}

void	traverse_list_to_add(t_envp *envp_head, char **key_and_value)
{
	t_envp	*target;

	target = find_node(envp_head, key_and_value[0]);
	if (target == NULL)
		add_new_node(envp_head->next, key_and_value);
	else
	{
		free(target->value);
		free(key_and_value[0]);
		target->value = key_and_value[1];
	}
}

void	builtin_export(t_cmd cmd, t_envp *envp_head)
{
	int		i;
	char	**arr;
	char	**key_and_value;

	arr = ft_split(cmd.command[1], ' ');
	i = 0;
	while (arr[i] != NULL)
	{
		key_and_value = divide_key_and_value(arr[i]);
		if (key_and_value != NULL)
		{
			if (first_character_check(key_and_value[0][0]) == 1)
				traverse_list_to_add(envp_head, key_and_value);
			else
			{
				free(key_and_value[0]);
				free(key_and_value[1]);
				printf("bash: export: '%s': not a valid identifier\n", arr[i]);
				errno = 1;
			}
			free(key_and_value);
		}
		free(arr[i++]);
	}
	free(arr);
}
