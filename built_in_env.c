/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:10 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 22:17:36 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(t_envp *head)
{
	t_envp	*lst;

	if (head == NULL)
		return ;
	lst = head->next;
	while (lst != NULL)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	// 마지막 줄 빼고 개행까지 diff로 비교 완료
	// _=/Users/seonjo/subjects/minishell/./a.out
	// _=/usr/bin/env
}
