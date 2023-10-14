/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:01:15 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 21:01:38 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	tr_overwrite_output(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd < 0)
		en_error();
	return (fd);
}

int	tr_append_output(char *file)
{
	int	fd;

	if (access(file, F_OK) == 0)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	else
		fd = open(file, O_WRONLY | O_APPEND);
	if (fd < 0)
		en_error();
	return (fd);
}

int	tr_file_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		en_error();
	return (fd);
}

void	tr_redirection(t_tree *tree, int fd[2])
{
	if (tree->left != NULL)
		tr_redirection(tree->left, fd);
	if (ft_strncmp(tree->str, ">", 2) == 0)
		fd[1] = tr_overwrite_output(tree->right);
	else if (ft_strncmp(tree->str, ">>", 3) == 0)
		fd[1] = tr_append_output(tree->right);
	else if (ft_strncmp(tree->str, "<", 2) == 0)
		fd[0] = tr_file_input(tree->right);
}
