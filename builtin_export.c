/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:53:25 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envs	*find_node(t_envs *envsp, char *key)
{
	t_envs	*node;
	int		key_len;

	key_len = ft_strlen(key);
	node = envsp->next;
	while (node != NULL)
	{
		if (ft_strncmp(key, node->key, key_len + 1) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	add_new_node(t_envs *now, char **key_and_value)
{
	t_envs	*next;

	if (now == NULL)
		now->next = make_envsp_node(key_and_value);
	else
	{
		next = now->next;
		while (next->next != NULL)
		{
			now = next;
			next = next->next;
		}
		now->next = make_envsp_node(key_and_value);
		now->next->next = next;
	}
}

void	traverse_list_to_add(t_envs *envsp, char **key_and_value)
{
	t_envs	*target;

	target = find_node(envsp, key_and_value[0]);
	if (target == NULL)
		add_new_node(envsp->next, key_and_value);
	else
	{
		free(target->value);
		target->value = key_and_value[1];
		free(key_and_value[0]);
		free(key_and_value);
	}
}

void	builtin_export(t_cmds *cmds, t_envs *envsp)
{
	int		i;
	char	*str;
	char	**key_and_value;

	errno = 0;
	i = 1;
	while (cmds->argv[i] != NULL)
	{
		str = cmds->argv[i++];
		key_and_value = divide_key_and_value(str);
		if (key_and_value != NULL)
		{
			if (is_valid_identifier(key_and_value[0]) == 1)
				traverse_list_to_add(envsp, key_and_value);
			else
			{
				free(key_and_value[0]);
				free(key_and_value[1]);
				free(key_and_value);
				printf("bash: export: '%s': not a valid identifier\n", str);
				errno = 1;
			}
		}
	}
}
