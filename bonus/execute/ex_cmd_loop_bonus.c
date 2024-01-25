/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:31:16 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/25 16:08:42 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

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
	envp = ft_calloc_s(sizeof(char *), size + 1);
	node = envsp->next;
	i = 0;
	while (i < size)
	{
		envp[i++] = ex_strjoin_c(node->key, node->value, '=');
		node = node->next;
	}
	envp[i] = NULL;
	return (envp);
}

pid_t	ex_fork(t_cmds *cmdsp, t_envs *envsp, char **envp, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"fork", strerror(errno)));
	else if (pid == 0)
	{
		sig_set(MODE_DEFAULT, MODE_DEFAULT);
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

void	ex_waitpid(pid_t pid)
{
	int	status;
	int	signal_flag;

	signal_flag = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) != 0)
		g_errno = WEXITSTATUS(status);
	if (WIFSIGNALED(status) != 0)
	{
		if (WTERMSIG(status) == SIGINT)
			signal_flag = 1;
		g_errno = WTERMSIG(status) + 128;
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 2);
	}
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WTERMSIG(status) == SIGINT)
			signal_flag = 1;
	}
	if (signal_flag == 1)
		ft_putstr_fd("\n", 2);
}

void	ex_cmd_loop(t_cmds *cmdsp_head, t_envs *envsp)
{
	t_cmds	*cmdsp;
	char	**envp;
	pid_t	pid;

	sig_set(MODE_IGNORE, MODE_IGNORE);
	sig_terminal_print_on();
	cmdsp = cmdsp_head->next;
	cmdsp->prev_out = -1;
	envp = NULL;
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
		ex_waitpid(pid);
	}
	ex_all_close(cmdsp_head, envp);
	sig_terminal_print_off();
	sig_set(MODE_SHELL, MODE_SHELL);
}
