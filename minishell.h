/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:46:51 by michang           #+#    #+#             */
/*   Updated: 2023/09/09 14:46:52 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include "libft/libft.h"
# include "libft_s/libft_s.h"
# include <errno.h>
# include <string.h>
# include "parser/parser.h"

# define MODE_SHELL 0
# define MODE_DEFAULT 1
# define MODE_IGNORE 2

void	set_signal(int sig_int, int sig_quit);
int		tk_tokenize(char *str, t_token **token_head);
int		mktr_make_tree(t_token *tk_head, t_tr_node **root);
void	trtv_start(t_tr_node *root, t_envs *envsp);

#endif
