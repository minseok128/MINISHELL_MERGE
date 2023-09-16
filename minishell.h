/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:24 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/16 16:31:51 by seonjo           ###   ########.fr       */
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
	char			*key;
	char			*value;
	struct s_envp	*next;
}t_envp;

void	lst_error(void);
char	**lst_divide_key_and_value(char *data);
t_envp	*lst_make_list(char **key_and_value);
t_envp	*lst_make_linkedlist(char **envp);
void	pw_pwd(void);
int		ex_first_character_check(char c);
t_envp	*ex_find_key(t_envp *head, char *key);
void	ex_export(t_envp *head, char *input);
void	un_unset(t_envp *head, char *input);
void	cd_cd(char *cmd);

#endif