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
	int		out_fd;
	char	*pwd;

	out_fd = btin_out_fd(cmds, fork_flag);
	if (out_fd == -1)
		return ;
	pwd = getcwd(NULL, 1024);
	if (pwd == NULL)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"getcwd", strerror(errno)));
	ft_putstr_fd(pwd, out_fd);
	ft_putchar_fd('\n', out_fd);
	free(pwd);
	if (out_fd != 1)
		close(out_fd);
	btin_out(fork_flag, 0, NULL);
}
