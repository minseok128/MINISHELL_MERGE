/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_make_envsp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/23 16:21:36 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	btin_free_key_and_value(char **key_and_value, char *key, char *value)
{
	free(key_and_value);
	free(key);
	if (value != NULL)
		free(value);
}

int	btin_find_equal_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**btin_divide_key_and_value(char *env)
{
	int		i;
	int		equal_index;
	char	**key_and_value;

	key_and_value = ft_calloc_s(sizeof(char *), 2);
	equal_index = btin_find_equal_index(env);
	if (equal_index == -1)
	{
		key_and_value[0] = ft_strdup_s(env);
		key_and_value[1] = NULL;
		return (key_and_value);
	}
	key_and_value[0] = ft_calloc_s(sizeof(char), (equal_index + 1));
	i = 0;
	while (env[i] != '=')
		key_and_value[0][i++] = env[i];
	key_and_value[1] = ft_strdup_s(env + (equal_index + 1));
	return (key_and_value);
}

t_envs	*btin_make_envsp_node(char **key_and_value)
{
	t_envs	*node;

	node = ft_calloc_s(sizeof(t_envs), 1);
	if (key_and_value != NULL)
	{
		node->key = key_and_value[0];
		node->value = key_and_value[1];
		free(key_and_value);
	}
	node->next = NULL;
	return (node);
}

t_envs	*btin_make_envsp(char **envp)
{
	t_envs	*envsp_head;
	t_envs	*envsp_tail;
	char	**key_and_value;
	int		i;

	envsp_head = btin_make_envsp_node(NULL);
	envsp_tail = envsp_head;
	i = 0;
	while (envp[i] != NULL)
	{
		key_and_value = btin_divide_key_and_value(envp[i]);
		envsp_tail->next = btin_make_envsp_node(key_and_value);
		envsp_tail = envsp_tail->next;
		i++;
	}
	return (envsp_head);
}