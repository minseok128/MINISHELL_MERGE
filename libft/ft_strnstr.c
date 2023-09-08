/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:45:23 by michang           #+#    #+#             */
/*   Updated: 2023/03/15 18:45:24 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;
	size_t			size;
	unsigned char	*str;
	unsigned char	*to_find;

	str = (unsigned char *)haystack;
	to_find = (unsigned char *)needle;
	size = ft_strlen((char *)to_find);
	if (!size)
		return ((char *)str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[i + j] && j + i < len)
			j++;
		if (size == j)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
