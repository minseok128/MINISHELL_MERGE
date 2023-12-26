/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:24 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/26 16:13:56 by seonjo           ###   ########.fr       */
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

typedef struct s_cmd
{
	char	**command;
	char	*input_file;
	char	*output_file;
}t_cmd;

// typedef struct s_fd
// {
// 	int			fd;
// 	struct s_fd	*next;
// }t_fd;

// typedef struct s_tree
// {
// 	char			*str;
// 	struct s_tree	*left;
// 	struct s_tree	*right;
// }t_tree;

void	builtin_error(void);
char	**divide_key_and_value(char *env);
t_envp	*make_env_node(char **key_and_value);
t_envp	*make_env(char **char_envp);
void	builtin_pwd(void);
int	is_valid_identifier(char *str);
t_envp	*find_node(t_envp *envp_head, char *key);
void	builtin_export(t_cmd *cmd, t_envp *envp_head);
void	builtin_unset(t_cmd *cmd, t_envp *envp_head);
void	builtin_cd(t_cmd *cmd, t_envp *envp_head);
void	builtin_echo(t_cmd *cmd);
void	builtin_env(t_envp *envp_head);
char	*ft__strdup(const char *s1);
// void	tr_all_close(t_fd *head);
// void	tr_lst_add(t_fd *head, int fd);
// void	tr_execute(t_tree *tree, t_envp *envp, int pipe_fd[2]);
// void	tr_redirection(t_tree *tree, int fd[2]);
// void	tr_preorder(t_envp *envp, t_tree *tree, t_fd *fdp, int flag);

#endif