/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_fd_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:15:50 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 21:45:42 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tr_lst_add(t_fd *head, int fd)
{
	t_fd	*new;

	new = malloc(sizeof(t_fd));
	if (new == 0)
		bi_error();
	new->fd = fd;
	new->next = head->next;
	head->next = new;
}

void	tr_all_close(t_fd *head)
{
	t_fd	*tmp;

	head = head->next;
	while (head != NULL)
	{
		tmp = head->next;
		close(head->fd);
		free(head);
		head = tmp;
	}
}
