/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:10 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/21 20:20:28 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_envp *envp_head)
{
	t_envp	*node;

	if (envp_head == NULL)
		return ;
	node = envp_head->next;
	while (node != NULL)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
	// 마지막 줄 빼고 개행까지 diff로 비교 완료
	// _=/Users/seonjo/subjects/minishell/./a.out
	// _=/usr/bin/env
}
