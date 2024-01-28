/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:44 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 18:57:05 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	btin_pwd(t_cmds *cmds, int fork_flag)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd == NULL)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"getcwd", strerror(errno)), cmds->enop);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	btin_out(fork_flag, 0, NULL, cmds->enop);
}
