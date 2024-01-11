/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:44:56 by michang           #+#    #+#             */
/*   Updated: 2023/03/15 18:44:56 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;

	src_len = ft_strlen(src);
	if (!dst)
		return (src_len);
	dest_len = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= dest_len)
		return (src_len + dstsize);
	i = 0;
	while (*(src + i) && i < dstsize - dest_len - 1)
	{
		*(dst + dest_len + i) = *(src + i);
		i++;
	}
	*(dst + dest_len + i) = '\0';
	return (dest_len + src_len);
}
