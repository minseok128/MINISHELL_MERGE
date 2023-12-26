/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:01 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/26 16:17:12 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		target->value = key_and_value[1];
		free(key_and_value[0]);
		free(key_and_value);
	}
}

void	builtin_export(t_cmd *cmd, t_envp *envp_head)
{
	int		i;
	char	*str;
	char	**key_and_value;

	errno = 0;
	i = 1;
	while (cmd->command[i] != NULL)
	{
		str = cmd->command[i++];
		key_and_value = divide_key_and_value(str);
		if (key_and_value != NULL)
		{
			if (is_valid_identifier(key_and_value[0]) == 1)
				traverse_list_to_add(envp_head, key_and_value);
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
