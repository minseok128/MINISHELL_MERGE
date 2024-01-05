/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:10 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:26:29 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	btin_env(t_envs *envsp, int fork_flag)
{
	t_envs	*node;

	if (envsp == NULL)
		return ;
	node = envsp->next;
	while (node != NULL)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	btin_out(fork_flag, 0, NULL);
	// 마지막 줄 빼고 개행까지 diff로 비교 완료
	// _=/Users/seonjo/subjects/minishell/./a.out
	// _=/usr/bin/env
}
