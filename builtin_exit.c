/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:55:22 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/05 11:41:25 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	btin_out(int fork_flag, int error_code, char *errmsg)
{
	if (errmsg != NULL)
		printf("%s", errmsg);
	if (fork_flag == 1)
		exit(error_code);
	else
		g_errno = error_code;
}

void	btin_exit(t_cmds *cmds, int fork_flag)
{
	int	n;

	printf("exit\n");
	if (cmds->argv[1] == NULL)
		btin_out(1, 0, NULL);
	else
	{
		n = ft__atoi(cmds->argv[1]);
		if (n == -1)
		{
			printf("bash: exit: %s: numeric argument required\n", cmds->argv[1]);
			btin_out(1, 255, NULL);
		}
		else if (cmds->argv[2] != NULL)
			btin_out(fork_flag, 255, "bash: exit: too many arguments\n");
		else
			btin_out(1, (char)n, NULL);
	}
}
