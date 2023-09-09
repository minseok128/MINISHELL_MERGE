/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:24 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/09 13:25:31 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include "./libft/libft.h"

typedef struct s_envp
{
	char			*str;
	struct s_envp	*next;
}t_envp;

int		can_export(char c);
void	ft_pwd(void);
void	ft_cd(char *path);
void	ft_export(t_envp *head, char *input);
void	ft_unset(t_envp *head, char *input);
void	error_and_exit(void);
t_envp	*make_linkedlist(char **envp);
t_envp	*make_lst(char *src);
t_envp	*find_env(t_envp *head, char *env);

#endif