/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:15:50 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/09 20:29:15 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add(t_lst *lst, int value)
{
	t_lst	*new;
	t_lst	*next;

	new = malloc(sizeof(t_lst));
	if (new == NULL)
		exit(1);
	next = lst->next;
	if (next != NULL)
		next->pre = new;
	lst->next = new;
	new->value = value;
	new->pre = lst;
	new->next = next;
}

void	lst_remove(t_lst *lst)
{
	if (lst->pre != NULL)
	{
		if (lst->next != NULL)
		{
			lst->pre->next = lst->next;
			lst->next->pre = lst->pre;
			free(lst);
		}
		else
		{
			lst->pre->next = NULL;
			free(lst);
		}
	}
}
