/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:37:01 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/10 17:16:08 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../btin/btin.h"

t_cmds	*ex_make_cmdsp(void);
void	ex_add_cmdsp_node(t_cmds *cmdsp, char **argv, char *in, char *out);
void	ex_process_command(t_cmds *cmds, t_envs *envsp);
void	ex_open_output_fd(t_cmds *cmdsp);
void	ex_open_input_fd(t_cmds *cmdsp);
void	ex_dup_to(int from, int to);
void	ex_execute(char **cmd, t_envs *envsp, char **envp);
int		ex_is_builtin(t_cmds *cmds, t_envs *envsp, int fork_flag);
char	*ex_strjoin_c(char const *s1, char const *s2, char c);
void	*ex_free_string_array(char **string_array);


#endif