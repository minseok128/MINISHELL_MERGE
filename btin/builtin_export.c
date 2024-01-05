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

#include "btin.h"

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
