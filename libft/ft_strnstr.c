/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:00:50 by seonjo            #+#    #+#             */
/*   Updated: 2023/03/18 22:21:35 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_cmp(char *haystack, char *needle, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (needle[j])
	{
		if (i == len)
			return (2);
		if (haystack[i] == needle[j])
		{
			i++;
			j++;
		}
		else
			return (0);
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		flag;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i])
	{
		if (i == len)
			return (0);
		if (haystack[i] == needle[0])
		{
			flag = c_cmp((char *)haystack, (char *)needle, i, len);
			if (flag == 1)
				return (&((char *)haystack)[i]);
			else if (flag == 2)
				return (0);
		}
		i++;
	}
	return (0);
}
