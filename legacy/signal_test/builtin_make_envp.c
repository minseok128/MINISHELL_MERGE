/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_make_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:24 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/26 19:43:30 by seonjo           ###   ########.fr       */
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

t_envp	*make_envp_node(char **key_and_value)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
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

t_envp	*make_envp(char **char_envp)
{
	t_envp	*envp_head;
	t_envp	*envp_tail;
	char	**key_and_value;
	int		i;

	envp_head = make_envp_node(NULL);
	envp_tail = envp_head;
	i = 0;
	while (char_envp[i] != NULL)
	{
		key_and_value = divide_key_and_value(char_envp[i]);
		envp_tail->next = make_envp_node(key_and_value);
		envp_tail = envp_tail->next;
		i++;
	}
	return (envp_head);
}
