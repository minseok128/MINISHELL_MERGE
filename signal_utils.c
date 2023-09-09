/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:46:32 by michang           #+#    #+#             */
/*   Updated: 2023/09/09 14:46:33 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	siganal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == MODE_SHELL)
		signal(SIGINT, siganal_handler);
	if (sig_quit == MODE_SHELL)
		signal(SIGQUIT, siganal_handler);
	if (sig_int == MODE_DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_quit == MODE_DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_int == MODE_IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_quit == MODE_IGNORE)
		signal(SIGQUIT, SIG_IGN);
}
