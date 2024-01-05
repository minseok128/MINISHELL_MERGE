/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:35:33 by michang           #+#    #+#             */
/*   Updated: 2023/03/21 21:35:34 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rst;
	t_list	*new_lst;
	t_list	*tmp;

	rst = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		new_lst = ft_calloc(1, sizeof(t_list));
		if (!new_lst)
		{
			ft_lstclear(&rst, del);
			return (0);
		}
		if (!rst)
			rst = new_lst;
		else
			tmp->next = new_lst;
		new_lst->content = (*f)(lst->content);
		tmp = new_lst;
		lst = lst->next;
	}
	return (rst);
}
