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

#include "../minishell.h"

void	test_cmds_print(t_cmds *cmds)
{
	int	i;

	i = 0;
	printf("[cmds print]\n");
	while (cmds)
	{
		printf("  #%d [cmd words]\n", i);
		for (int j = 0; j < cmds->argv.size; j++)
		{
			printf("    #%d-%d: %s\n", i, j, (char *)(cmds->argv.items[j]));
		}
		cmds = cmds->next;
		i++;
	}
	printf("\n");
}
