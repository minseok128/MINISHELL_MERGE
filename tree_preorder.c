/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_preorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:58:17 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:23:21 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tr_is_builtin(t_tree *tree, t_envs *envp)
{
	char	*cmd;

	cmd = tree->str;
	if (ft_strncmp(cmd, "cd", 3) == 0)
		bi_cd(tree->right->str);
	// 공사중
	// else if (ft_strncmp(cmd, "echo", 5) == 0)
	// 	bi_echo(tree);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		bi_env(envp);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		bi_export(envp, tree->str);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		bi_unset(envp, tree->str);
	else
		return (0);
	return (1);
}

void	tr_fork(t_tree *tree, t_envs *envp, int pipe_fd[2], int input_fd)
{
	pid_t	pid;

	if (input_fd == 0 && tr_is_builtin(tree, envp) == 1)
		return ;
	else
	{
		pid = fork();
		if (pid == -1)
			bi_error();
		else if (pid == 0)
		{
			close(pipe_fd[0]);
			pipe_fd[0] = input_fd;
			if (tree->left != NULL)
				tr_redirection(tree->left, pipe_fd);
			tr_execute(tree->right, envp, pipe_fd);
		}
		close(pipe_fd[1]);
	}
}

void	tr_pipe(t_tree *tree, t_fd *fdp, t_envs *envp, int input_fd)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		bi_error();
	tr_lst_add(fdp, pipe_fd[1]);
	tr_lst_add(fdp, pipe_fd[0]);
	tr_fork(tree, envp, pipe_fd, input_fd);
}

int	tr_get_input_fd(t_fd *pre_fd)
{
	if (pre_fd != NULL)
		return (pre_fd->fd);
	else
		return (0);
}

void	tr_preorder(t_envs *envp, t_tree *tree, t_fd *fdp, int flag)
{
	int	fd[2];
	int	input_fd;	

	fd[0] = 0;
	fd[1] = 1;
	input_fd = tr_get_input_fd(fdp->next);
	if (tree->str == NULL)
		return ;
	if (ft_strncmp(tree->str, "|", 2) == 0)
	{
		tr_pipe(tree->left, fdp, envp, input_fd);
		tr_preorder(envp, tree->right, fdp, 0);
	}
	else if (tree->str[0] == '>' || tree->str[0] == '<')
		tr_redirection(tree, fd);
	else
		tr_fork(tree, envp, fd, input_fd);
	if (flag == 1)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		tr_all_close(fdp);
	}
}
