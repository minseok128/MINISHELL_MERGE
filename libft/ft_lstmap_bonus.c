/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:14:27 by seonjo            #+#    #+#             */
/*   Updated: 2023/03/19 17:08:09 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*make_tmp(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*con;
	t_list	*tmp;

	con = f(lst -> content);
	tmp = ft_lstnew(con);
	if (tmp == 0)
		del(con);
	return (tmp);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*tmp;

	if (lst == 0)
		return (0);
	first = make_tmp(lst, f, del);
	if (first == 0)
		return (0);
	lst = lst -> next;
	while (lst)
	{
		tmp = make_tmp(lst, f, del);
		if (tmp == 0)
		{
			ft_lstclear(&first, del);
			return (0);
		}
		ft_lstadd_back(&first, tmp);
		lst = lst -> next;
	}
	return (first);
}
