/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:24 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 21:01:52 by seonjo           ###   ########.fr       */
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

int	g_errno;

void	btin_pwd(void);
void	btin_export(t_cmds *cmds, t_envs *envsp);
void	btin_unset(t_cmds *cmds, t_envs *envsp);
void	btin_cd(t_cmds *cmds, t_envs *envsp);
void	btin_echo(t_cmds *cmds);
void	btin_env(t_envs *envsp);
char	*ft__strdup(const char *s1);
char	**btin_divide_key_and_value(char *env);
t_envs	*btin_make_envsp_node(char **key_and_value);
t_envs	*btin_make_envsp(char **envp);
int		btin_is_valid_identifier(char *str);
t_envs	*btin_find_node(t_envs *envsp, char *key);
void	btin_error(void);
int		ex_process_command(t_cmds *cmds, t_envs *envsp);

#endif