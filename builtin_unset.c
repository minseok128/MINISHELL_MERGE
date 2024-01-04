/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:19 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:26:29 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!(str[0] >= 'a' && str[0] <= 'z') && \
		!(str[0] >= 'A' && str[0] <= 'Z') && \
		!(str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 'a' && str[i] <= 'z') && \
			!(str[i] >= 'A' && str[i] <= 'Z') && \
			!(str[i] >= '0' && str[i] <= '9') && \
			!(str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	remove_envsp_node(t_envs *envsp, char *key)
{
	t_envs	*now;
	t_envs	*next;
	t_envs	*target;

	target = find_node(envsp, key);
	if (target != NULL)
	{
		now = envsp;
		next = now->next;
		while (next != target)
		{
			now = next;
			next = next->next;
		}
		now->next = next->next;
		free(next->key);
		free(next->value);
		free(next);
	}
}

void	builtin_unset(t_cmds *cmds, t_envs *envsp)
{
	int		i;
	int		j;
	char	*str;

	errno = 0;
	i = 1;
	while (cmds->argv[i] != NULL)
	{
		str = cmds->argv[i++];
		j = 0;
		if (is_valid_identifier(str) == 1)
			remove_envsp_node(envsp, str);
		else
		{
			printf("bash: unset: '%s': not a valid identifier\n", str);
			errno = 1;
		}
	}
}
