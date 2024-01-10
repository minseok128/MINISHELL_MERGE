/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:18:04 by michang           #+#    #+#             */
/*   Updated: 2024/01/10 21:18:05 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

void	test_cmds_print(t_vector *cmds)
{
	for (int i = 0; i < cmds->size; i++)
	{
		printf("#%d [cmd words]\n", i);
		for (int j = 0; j < ((t_cmd *)(cmds->items[i]))->argv.size; j++)
		{
			printf("#%d-%d: %s\n", i, j, ((t_cmd *)(cmds->items[i]))->argv.items[i]);
		}
		printf("\n");
	}
}
