/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:45:35 by michang           #+#    #+#             */
/*   Updated: 2023/03/15 18:45:36 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = malloc(count * size);
	if (!new)
		return (0);
	ft_memset(new, 0, count * size);
	return (new);
}

void	*ft_calloc_s(size_t count, size_t size)
{
	void	*new;

	if (!size)
		return (0);
	new = malloc(count * size);
	if (!new)
		exit(1);
	ft_memset(new, 0, count * size);
	return (new);
}
