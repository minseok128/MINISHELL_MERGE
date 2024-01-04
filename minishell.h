/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:52:16 by seonjo           ###   ########.fr       */
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

typedef struct s_envsp
{
	char			*key;
	char			*value;
	struct s_envsp	*next;
}	t_envs;

typedef struct s_cmds
{
	char			**argv;
	char			*in_file;
	char			*out_file;
	struct s_cmds	*next;
}	t_cmds;

void	builtin_pwd(void);
void	builtin_export(t_cmds *cmds, t_envs *envsp);
void	builtin_unset(t_cmds *cmds, t_envs *envsp);
void	builtin_cd(t_cmds *cmds, t_envs *envsp);
void	builtin_echo(t_cmds *cmds);
void	builtin_env(t_envs *envsp);
char	*ft__strdup(const char *s1);
char	**divide_key_and_value(char *env);
t_envs	*make_envsp_node(char **key_and_value);
t_envs	*make_envsp(char **envp);
int		is_valid_identifier(char *str);
t_envs	*find_node(t_envs *envsp, char *key);
void	builtin_error(void);
int		ex_process_command(t_cmds *cmds, t_envs *envsp);

#endif