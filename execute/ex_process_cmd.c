/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_process_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:31:16 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/10 16:41:59 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*ex_strjoin_c(char const *s1, char const *s2, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = ft_calloc_s(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

int	ex_is_builtin(t_cmds *cmds, t_envs *envsp, int fork_flag)
{
	if (ft_strncmp(cmds->argv[0], "cd", 3) == 0)
		btin_cd(cmds, envsp, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "pwd", 4) == 0)
		btin_pwd(fork_flag);
	else if (ft_strncmp(cmds->argv[0], "export", 7) == 0)
		btin_export(cmds, envsp, 0, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "unset", 6) == 0)
		btin_unset(cmds, envsp, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "echo", 5) == 0)
		btin_echo(cmds, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "env", 4) == 0)
		btin_env(envsp, fork_flag);
	else if (ft_strncmp(cmds->argv[0], "exit", 5) == 0)
		btin_exit(cmds, fork_flag);
	else
		return (0);
	return (1);
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
	envp = malloc(sizeof(char *) * (size + 1));
	node = envsp->next;
	i = 0;
	while (i < size)
		envp[i++] = ex_strjoin_c(node->key, node->value, '=');
	envp[i] = NULL;
	return (envp);
}

void	ex_dup_to(int from, int to)
{
	if (dup2(from, to) == -1)
		btin_out(1, errno, strerror(errno));
}

void	*ex_free_string_array(char **string_array)
{
	int	i;

	i = 0;
	while (string_array[i] != NULL)
	{
		free(string_array[i]);
		i++;
	}
	return (NULL);
}

char	*ex_search_path(char *cmd, t_envs *envsp)
{
	char	**envp_path;
	char	*path;
	int		i;

	while (envsp != NULL && ft_strncmp(envsp->key, "PATH", 5) != 0)
		envsp = envsp->next;
	if (envsp == NULL)
		return (cmd);
	envp_path = ft_split(envsp->value + 5, ':');
	i = 0;
	while (envp_path[i] != NULL)
	{
		path = ex_strjoin_c(envp_path[i++], cmd, '/');
		if (path == NULL)
			btin_out(1, errno, strerror(errno));
		if (access(path, F_OK) == 0)
		{
			// free(cmd);
			ex_free_string_array(envp_path);
			return (path);
		}
		free(path);
	}
	ex_free_string_array(envp_path);
	return (cmd);
}

void	ex_execute(char **cmd, t_envs *envsp, char **envp)
{
	t_envs	*envsp_cp;

	envsp_cp = envsp->next;
	if (access(cmd[0], F_OK) == -1)
		cmd[0] = ex_search_path(cmd[0], envsp_cp);
	if (execve(cmd[0], cmd, envp) == -1)
		btin_out(1, errno, strerror(errno));
}

void	ex_open_input_fd(t_cmds *cmdsp)
{
	int	in_fd;

	if (access(cmdsp->in_file, F_OK) != 0)
	{
		printf("bash: %s: No such file or directory\n", cmdsp->in_file);
		btin_out(1, 1, NULL);
	}
	in_fd = open(cmdsp->in_file, O_RDONLY);
	if (in_fd == -1)
	{
		printf("bash: %s: Permission denied\n", cmdsp->in_file);
		btin_out(1, 1, NULL);
	}
	ex_dup_to(in_fd, 0);
}

void	ex_open_output_fd(t_cmds *cmdsp)
{
	int	out_fd;

	if (cmdsp->type == APPEND)
		out_fd = open(cmdsp->out_file, O_WRONLY | O_APPEND);
	else
		out_fd = open(cmdsp->out_file, O_WRONLY);
	if (out_fd == -1)
	{
		printf("bash: %s: Permission denied\n", cmdsp->out_file);
		btin_out(1, 1, NULL);
	}
	ex_dup_to(out_fd, 1);
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
		ex_execute(cmdsp->argv, envsp, envp);
	}
	return (pid);
}

pid_t	ex_do_pipe(t_cmds *cmdsp, t_envs *envsp, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (ex_is_builtin(cmdsp, envsp, 1) == 0)
	{
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
	return (0);
}

void	ex_all_close(t_cmds *cmdsp)
{
	t_cmds	*tmp;

	while (cmdsp != NULL)
	{
		// ex_free_string_array(cmdsp->argv);
		free(cmdsp->argv);
		//	
		// if (cmdsp->in_file != NULL)
		// 	free(cmdsp->in_file);
		// if (cmdsp->out_file != NULL)
		// 	free(cmdsp->out_file);
		tmp = cmdsp;
		cmdsp = cmdsp->next;
		free(tmp);
	}
}

void	ex_process_command(t_cmds *cmdsp_head, t_envs *envsp)
{
	t_cmds	*cmdsp;
	char	**envp;
	int		status;
	pid_t	pid;

	cmdsp = cmdsp_head->next;
	cmdsp->prev_out = -1;
	//단일 builtin 명령어 처리
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
	}
	ex_all_close(cmdsp_head->next);
}
