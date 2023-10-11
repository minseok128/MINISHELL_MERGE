/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_preorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:58:17 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/11 15:38:52 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tr_overwrite(char *file, t_lst *fd_head)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd < 0)
		en_error();
	lst_add(fd_head, fd);
	return (fd);
}

int	tr_append(char *file, t_lst *fd_head)
{
	int	fd;

	if (access(file, F_OK) == 0)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	else
		fd = open(file, O_WRONLY | O_APPEND);
	if (fd < 0)
		en_error();
	lst_add(fd_head, fd);
	return (fd);
}

//int	tr_file_input(char *file, t_lst *fd_head)
//{
	
//}

//int	tr_stdin_input(char *limiter, t_lst *fd_head)
//{
		
//}

void	tr_redirection(t_tree *tree, t_lst *pid_head, t_lst *fd_head, int *fd)
{
	if (tree->left != NULL)
		tr_redirection(tree->left, pid_head, fd_head, fd);
	if (ft_strncmp(tree->str, ">", 2) == 0)
		fd[1] = tr_overwrite(tree->right, fd_head);
	else if (ft_strncmp(tree->str, ">>", 3) == 0)
		fd[1] = tr_append(tree->right, fd_head);
	else if (ft_strncmp(tree->str, "<", 2) == 0)
		fd[0] = tr_file_input(tree->right, fd_head);
	else
		fd[0] = tr_stdin_input(tree->right, fd_head);
}

void	tr_pipe(t_tree *tree, t_lst *pid_head, t_lst *fd_head)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		en_error();
	else if (pid == 0)
	{
		tr_preorder(tree->left, pid_head, fd_head, 0);
	}
	else
	{
		lst_add(pid_head, pid);
		tr_preorder(tree->right, pid_head, fd_head, 0);
	}
}
void	tr_wait_child_process(t_lst *pid_head, t_lst *fd_head)
{
	t_lst	*tmp;

	while (pid_head->value > 0)
	{
		tmp = pid_head->next;
		while (tmp != NULL)
		{
			if (waitpid(tmp->value, WNOHANG) != 0)
			{
				tmp = tmp->next;
				lst_remove(tmp->pre);
				pid_head->value--;
			}
			else
				tmp = tmp->next;
		}
	}
}

void	tr_preorder(t_tree *tree, t_lst *pid_head, t_lst *fd_head, int flag)
{
	int	fd[2];

	fd[0] = 0;
	fd[1] = 1;
	if (tree->str == NULL)
		return ;
	if (ft_strncmp(tree->str, "|", 2) == 0)
		tr_pipe(tree, pid_head, fd_head);
	else if (tree->str[0] == '>' || tree->str[0] == '<')
		tr_redirection(tree, pid_head, fd_head, fd);
	else
		
	if (pid_head->value > 0 && flag == 1)
		tr_wait_child_process(pid_head);
}
