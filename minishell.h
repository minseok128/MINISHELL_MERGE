/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:24 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 22:47:08 by seonjo           ###   ########.fr       */
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
	struct s_fd	*next;
}t_fd;

typedef struct s_tree
{
	char			*str;
	struct s_tree	*left;
	struct s_tree	*right;
}t_tree;

void	bi_error(void);
char	**bi_divide_key_and_value(char *data);
t_envp	*bi_make_list(char **key_and_value);
t_envp	*bi_make_linkedlist(char **envp);
void	bi_pwd(void);
int		bi_first_character_check(char c);
t_envp	*bi_find_key(t_envp *head, char *key);
void	bi_export(t_envp *head, char *input);
void	bi_unset(t_envp *head, char *input);
void	bi_cd(char *cmd);
void	bi_env(t_envp *head);
void	tr_all_close(t_fd *head);
void	tr_lst_add(t_fd *head, int fd);
void	tr_execute(t_tree *tree, t_envp *envp);
void	tr_redirection(t_tree *tree, int fd[2]);
void	tr_preorder(t_envp *envp, t_tree *tree, t_fd *fdp, int flag);

#endif