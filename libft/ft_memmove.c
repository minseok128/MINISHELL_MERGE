/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:04:05 by seonjo            #+#    #+#             */
/*   Updated: 2023/03/18 21:14:44 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rev(unsigned char *s, unsigned char *d, size_t i, size_t len)
{
	if (len != 0)
	{
		i = len - 1;
		s += i;
		d += i;
		while (i-- > 0)
			*d-- = *s--;
		*d = *s;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (0);
	if (dst < src)
	{
		i = 0;
		while (i++ < len)
			*d++ = *s++;
	}
	else
		rev(s, d, len - 1, len);
	return (dst);
}
