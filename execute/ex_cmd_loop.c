/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:31:16 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/17 16:07:08 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ex_all_close(t_cmds *cmdsp)
{
	// t_cmds	*tmp;

	while (cmdsp != NULL)
	{
		if ((cmdsp->type & RD_HEREDOC) != 0)
			if (unlink(cmdsp->in_file) == -1)
				exit(1);
		// ex_free_string_array(cmdsp->argv);
		// free(cmdsp->argv);
		// if (cmdsp->in_file != NULL)
		// 	free(cmdsp->in_file);
		// if (cmdsp->out_file != NULL)
		// 	free(cmdsp->out_file);
		// tmp = cmdsp;
		cmdsp = cmdsp->next;
		// free(tmp);
	}
}

char	**ex_change_to_envp(t_envs *envsp)
{
	t_envs	*node;
	char	**envp;
	int		size;
	int		i;

	size = 0;
	node = envsp->next;
	while (node->next != NULL)
	{
		node = node->next;
		size++;
	}
	envp = malloc(sizeof(char *) * (size));
	node = envsp->next;
	i = 0;
	while (i < size)
		envp[i++] = ex_strjoin_c(node->key, node->value, '=');
	envp[i] = NULL;
	return (envp);
}

pid_t	ex_fork(t_cmds *cmdsp, t_envs *envsp, char **envp, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		btin_out(1, errno, strerror(errno));
	else if (pid == 0)
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (cmdsp->in_file != NULL)
			ex_open_input_fd(cmdsp);
		else if (cmdsp->prev_out != -1)
			ex_dup_to(cmdsp->prev_out, 0);
		if (cmdsp->out_file != NULL)
			ex_open_output_fd(cmdsp);
		else if (pipe_fd[1] != -1)
			ex_dup_to(pipe_fd[1], 1);
		if (ex_is_builtin(cmdsp, envsp, 1) == 0)
			ex_execute((char **)(cmdsp->argv.items), envsp, envp);
	}
	return (pid);
}

pid_t	ex_do_pipe(t_cmds *cmdsp, t_envs *envsp, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (cmdsp->next == NULL)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		pid = ex_fork(cmdsp, envsp, envp, pipe_fd);
		close(cmdsp->prev_out);
	}
	else
	{
		pipe(pipe_fd);
		pid = ex_fork(cmdsp, envsp, envp, pipe_fd);
		close(pipe_fd[1]);
		if (cmdsp->prev_out != -1)
			close(cmdsp->prev_out);
		cmdsp->next->prev_out = pipe_fd[0];
	}
	return (pid);
}

void	ex_cmd_loop(t_cmds *cmdsp_head, t_envs *envsp)
{
	t_cmds	*cmdsp;
	char	**envp;
	int		status;
	pid_t	pid;

	cmdsp = cmdsp_head->next;
	cmdsp->prev_out = -1;
	if (cmdsp->next == NULL && ex_is_builtin(cmdsp, envsp, 0) == 1)
		;
	else
	{
		envp = ex_change_to_envp(envsp);
		while (cmdsp != NULL)
		{
			pid = ex_do_pipe(cmdsp, envsp, envp);
			cmdsp = cmdsp->next;
		}
		waitpid(pid, &status, 0);
		while (waitpid(-1, NULL, 0) != -1)
			;
		if (WIFEXITED(status) != 0)
			g_errno = WEXITSTATUS(status);
		if (WIFSIGNALED(status) != 0)
			g_errno = WTERMSIG(status) + 128;
		printf("g_errno : %d\n", g_errno);
	}
	ex_all_close(cmdsp_head->next);
}
