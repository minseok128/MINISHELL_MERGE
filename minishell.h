/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:24 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 21:01:45 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "get_next_line.h"
# include "./libft/libft.h"

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}t_envp;

typedef struct s_fd
{
	int				fd;
	struct s_lst	*next;
}t_fd;

typedef struct s_tree
{
	char			*str;
	struct s_tree	*left;
	struct s_tree	*right;
}t_tree;

void	fd_all_close(t_fd *head);
void	fd_lst_add(t_fd *head, int fd);
void	en_error(void);
char	**en_divide_key_and_value(char *data);
t_envp	*en_make_list(char **key_and_value);
t_envp	*en_make_linkedlist(char **envp);
void	pw_pwd(void);
int		ex_first_character_check(char c);
t_envp	*ex_find_key(t_envp *head, char *key);
void	ex_export(t_envp *head, char *input);
void	un_unset(t_envp *head, char *input);
void	cd_cd(char *cmd);
void	en_env(t_envp *head);
void	tr_execute(t_tree *tree, char **envp);
void	tr_redirection(t_tree *tree, int fd[2]);

#endif