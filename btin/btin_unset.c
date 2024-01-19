/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:19 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/19 15:04:21 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	btin_export_print(t_envs *envsp, int fork_flag)
{
	t_envs	*node;

	node = envsp->next;
	while (node != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(node->key, 1);
		if (node->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(node->value, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		node = node->next;
	}
}

int	btin_is_valid_identifier(char *str)
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

void	btin_remove_envsp_node(t_envs *envsp, char *key)
{
	t_envs	*now;
	t_envs	*next;
	t_envs	*target;

	target = btin_find_node(envsp, key);
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
		if (next->value != NULL)
			free(next->value);
		free(next);
	}
}

void	btin_unset(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	int		i;
	char	*str;
	int		error_flag;

	error_flag = 0;
	i = 1;
	while (cmds->argv.items[i] != NULL)
	{
		str = cmds->argv.items[i++];
		if (btin_is_valid_identifier(str) == 1)
			btin_remove_envsp_node(envsp, str);
		else
		{
			btin_out(0, 0, btin_make_errmsg("minishell: unset: '", \
				ft_strjoin_s(str, "'"), "not a valid identifier"));
			error_flag = 1;
		}
	}
	btin_out(fork_flag, error_flag, NULL);
}
