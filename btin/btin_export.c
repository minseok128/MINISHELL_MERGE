/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 18:52:22 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envs	*btin_find_node(t_envs *envsp, char *key)
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

void	btin_add_new_node(t_envs *envsp, char **key_and_value)
{
	t_envs	*now;
	t_envs	*next;

	now = envsp;
	next = now->next;
	while (next != NULL)
	{
		now = next;
		next = now->next;
	}
	now->next = btin_make_envsp_node(key_and_value);
}

void	btin_traverse_list_to_add(t_envs *envsp, char **key_and_value)
{
	t_envs	*target;

	target = btin_find_node(envsp, key_and_value[0]);
	if (target == NULL)
		btin_add_new_node(envsp, key_and_value);
	else if (key_and_value[1] != NULL)
	{
		if (target->value != NULL)
			free(target->value);
		target->value = key_and_value[1];
		btin_free_key_and_value(key_and_value, key_and_value[0], NULL);
	}
	else
		btin_free_key_and_value(key_and_value, key_and_value[0], NULL);
}

void	btin_export(t_cmds *cmds, t_envs *envsp, int error_code, int fork_flag)
{
	int		i;
	char	*str;
	char	**key_value;

	i = 1;
	if (cmds->argv.items[i] == NULL)
		btin_export_print(envsp);
	while (cmds->argv.items[i] != NULL)
	{
		str = cmds->argv.items[i++];
		key_value = btin_divide_key_and_value(str);
		if (key_value != NULL)
		{
			if (btin_is_valid_identifier(key_value[0]) == 1)
				btin_traverse_list_to_add(envsp, key_value);
			else
			{
				btin_free_key_and_value(key_value, key_value[0], key_value[1]);
				str = ft_strjoin_s(str, "'");
				btin_out(0, 0, btin_make_errmsg("minishell: export: `", str, \
					"not a valid identifier"));
				free(str);
				error_code = 1;
			}
		}
	}
	btin_out(fork_flag, error_code, NULL);
}
