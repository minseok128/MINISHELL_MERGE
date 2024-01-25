/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:32:36 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/24 16:33:09 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	btin_export_print(t_envs *envsp)
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

int	btin_export_error(char **key_value, char *str)
{
	char	*tmp_str;

	btin_free_key_and_value(key_value, key_value[0], key_value[1]);
	tmp_str = ft_strjoin_s(str, "'");
	btin_out(0, 0, btin_make_errmsg("minishell: export: '", tmp_str, \
		"not a valid identifier"));
	free(tmp_str);
	return (1);
}
