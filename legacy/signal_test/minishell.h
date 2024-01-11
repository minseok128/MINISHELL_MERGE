/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:46:51 by michang           #+#    #+#             */
/*   Updated: 2024/01/03 17:39:18 by seonjo           ###   ########.fr       */
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
# define MODE_HEREDOC 3

# define T_PIPE 11
# define T_SL_DIREC 12
# define T_SR_DIREC 13
# define T_DL_DIREC 14
# define T_DR_DIREC 15

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
} t_envp;

typedef	struct s_token {
	int				type;
	char			*str;
	struct s_token *next;
} t_token;

typedef struct s_cmd
{
	char	**command;
	char	*input_file;
	char	*output_file;
}t_cmd;

t_envp	*make_envp(char **char_envp);
void	builtin_env(t_envp *envp_head);
void	set_signal(int sig_int, int sig_quit);
void	parse(char *str, t_envp *head);

#endif
