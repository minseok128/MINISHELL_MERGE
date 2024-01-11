/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:45:25 by michang           #+#    #+#             */
/*   Updated: 2023/03/15 18:45:26 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			len;
	char			new_c;
	char			*str;

	new_c = (char)c;
	str = (char *)s;
	len = ft_strlen(s);
	if (new_c == 0)
		return (str + len);
	if (len == 0)
		return (0);
	len--;
	while (len > 0)
	{
		if (str[len] == new_c)
			return (str + len);
		len--;
	}
	if (str[0] == new_c)
		return (str);
	return (0);
}
