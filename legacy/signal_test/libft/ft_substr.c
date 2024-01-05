/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:07:03 by michang           #+#    #+#             */
/*   Updated: 2023/03/18 22:07:09 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	s_len;
	size_t			real_len;
	char			*new;	

	s_len = (unsigned int)ft_strlen(s);
	real_len = 0;
	if (start >= s_len)
		real_len = 0;
	else
	{
		while (real_len < len && s[start + real_len])
			real_len++;
	}
	new = ft_calloc(real_len + 1, sizeof(char));
	if (!new)
		return (0);
	i = 0;
	while (i < real_len)
	{
		new[i] = s[start + i];
		i++;
	}
	return (new);
}
