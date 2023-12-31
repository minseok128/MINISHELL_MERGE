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
# include <errno.h>
# include <string.h>

# define MODE_SHELL 0
# define MODE_DEFAULT 1
# define MODE_IGNORE 2

typedef enum e_token_type {
	T_AND = 10,
	T_OR,
	T_PIPE,
	T_PARENT_L,
	T_PARENT_R,
	T_REDIR_S_L,
	T_REDIR_S_R,
	T_REDIR_D_L,
	T_REDIR_D_R,
	T_WORD,
	T_NULL = 98,
	T_UNDEFINED = 99
} t_token_type;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
} t_envp;

typedef	struct s_token {
	t_token_type	type;
	int				flag;
	char			*str;
	struct s_token *next;
} t_token;

t_envp	*env_init_list_s(char **envp);
void	env_print(t_envp *head);
void	set_signal(int sig_int, int sig_quit);
t_envp	*envi_make_linkedlist(char **envp);
t_envp	*ex_find_key(t_envp *head, char *key);
void	tk_tokenize(char *str);

#endif
