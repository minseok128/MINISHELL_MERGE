/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:15:27 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/05 21:22:58 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTIN_H
# define BTIN_H

# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "../libft_s/libft_s.h"

typedef struct s_envsp
{
	char			*key;
	char			*value;
	struct s_envsp	*next;
}	t_envs;

typedef struct s_cmds
{
	char			**argv;
	int				in_file;
	int				out_file;
	struct s_cmds	*next;
}	t_cmds;

int			g_errno;

void		btin_pwd(int fork_flag);
void		btin_export(t_cmds *cmds, t_envs *envsp, int error_code, int fork_flag);
void		btin_unset(t_cmds *cmds, t_envs *envsp, int fork_flag);
void		btin_cd(t_cmds *cmds, t_envs *envsp, int fork_flag);
void		btin_echo(t_cmds *cmds, int fork_flag);
void		btin_env(t_envs *envsp, int fork_flag);
void		btin_exit(t_cmds *cmds, int fork_flag);
void		btin_out(int fork_flag, int error_code, char *errmsg);
int			btin_is_valid_identifier(char *str);
void		btin_print_declare_env(t_envs *envsp);
void		btin_free_key_and_value(char **key_and_value, char *key, char *value);
t_envs		*btin_make_envsp_node(char **key_and_value);
t_envs		*btin_make_envsp(char **envp);
t_envs		*btin_find_node(t_envs *envsp, char *key);
char		**btin_divide_key_and_value(char *env);


#endif