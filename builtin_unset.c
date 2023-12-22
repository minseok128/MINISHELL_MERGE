/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:19 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/22 19:27:48 by seonjo           ###   ########.fr       */
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

void	remove_env_node(t_envp *envp_head, char *key)
{
	t_envp	*now;
	t_envp	*next;
	t_envp	*target;

	target = find_node(envp_head, key);
	if (target != NULL)
	{
		now = envp_head;
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

void	builtin_unset(t_cmd *cmd, t_envp *envp_head)
{
	int		i;
	int		j;
	char	*str;

	errno = 0;
	i = 1;
	while (cmd->command[i] != NULL)
	{
		str = cmd->command[i++];
		j = 0;
		if (first_character_check(str[0]) == 1)
			remove_env_node(envp_head, str);
		else
		{
			printf("bash: unset: '%s': not a valid identifier\n", str);
			errno = 1;
		}
	}
}
