/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:46:32 by michang           #+#    #+#             */
/*   Updated: 2024/01/12 16:14:11 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_heredoc_handler(int signo)
{
	(void)signo;
	printf("\n");
	exit(1);
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == MODE_SHELL)
		signal(SIGINT, signal_handler);
	if (sig_quit == MODE_SHELL)
		signal(SIGQUIT, SIG_IGN);
	if (sig_int == MODE_DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_quit == MODE_DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_int == MODE_IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_quit == MODE_IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_int == MODE_HEREDOC)
		signal(SIGINT, signal_heredoc_handler);
	if (sig_quit == MODE_HEREDOC)
		signal(SIGQUIT, SIG_IGN);
}
