/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_make_envsp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:19:32 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_error(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

int	find_equal_index(char *str)
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

char	**divide_key_and_value(char *env)
{
	int		equal_index;
	char	**key_and_value;

	key_and_value = malloc(sizeof(char *) * 2);
	if (key_and_value == NULL)
		builtin_error();
	equal_index = find_equal_index(env);
	if (equal_index == -1)
		return (NULL);
	key_and_value[0] = malloc(sizeof(char) * (equal_index + 1));
	if (key_and_value[0] == NULL)
		builtin_error();
	ft_strlcpy(key_and_value[0], env, equal_index + 1);
	key_and_value[1] = ft_strdup(env + (equal_index + 1));
	return (key_and_value);
}

t_envs	*make_envsp_node(char **key_and_value)
{
	t_envs	*node;

	node = malloc(sizeof(t_envs));
	if (node == NULL)
		builtin_error();
	if (key_and_value != NULL)
	{
		node->key = key_and_value[0];
		node->value = key_and_value[1];
		free(key_and_value);
	}
	node->next = NULL;
	return (node);
}

t_envs	*make_envsp(char **envp)
{
	t_envs	*envsp_head;
	t_envs	*envsp_tail;
	char	**key_and_value;
	int		i;

	envsp_head = make_envsp_node(NULL);
	envsp_tail = envsp_head;
	i = 0;
	while (envp[i] != NULL)
	{
		key_and_value = divide_key_and_value(envp[i]);
		envsp_tail->next = make_envsp_node(key_and_value);
		envsp_tail = envsp_tail->next;
		i++;
	}
	return (envsp_head);
}
