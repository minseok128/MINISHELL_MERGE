/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:48:56 by seonjo            #+#    #+#             */
/*   Updated: 2023/03/18 21:31:20 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	i = len_d;
	if (size <= len_d)
		return (len_s + size);
	if (*src)
	{
		while (size > 1 + i)
		{
			if (*src)
				dest[i++] = *src++;
			else
				break ;
		}
		dest[i] = 0;
	}
	return (len_s + len_d);
}
