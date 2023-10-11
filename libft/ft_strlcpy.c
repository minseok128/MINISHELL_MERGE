/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:42:17 by seonjo            #+#    #+#             */
/*   Updated: 2023/03/18 21:26:07 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	j = 0;
	n = ft_strlen(src);
	if (size > 0)
	{
		while (size-- > 1 && i < n)
		{
			if (src[i])
			{
				dest[i] = src[i];
				i++;
			}
		}
		dest[i] = 0;
	}
	while (src[j])
		j++;
	return (j);
}
