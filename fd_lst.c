/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:15:50 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/14 16:28:10 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_lst_add(t_fd *head, int fd)
{
	t_fd	*new;

	new = malloc(sizeof(t_fd));
	if (new == 0)
		en_error();
	new->fd = fd;
	new->next = head->next;
	head->next = new;
}

void	fd_all_close(t_fd *head)
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
