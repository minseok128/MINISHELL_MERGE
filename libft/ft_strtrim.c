/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:30:25 by michang           #+#    #+#             */
/*   Updated: 2023/03/19 12:30:29 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char const *set, char c)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*new;
	unsigned int	start;
	unsigned int	end;
	unsigned int	i;

	i = ft_strlen(s1);
	start = 0;
	while (ft_is_set(set, s1[start]))
		start++;
	end = i - 1;
	if (start == i)
		return (ft_calloc(1, sizeof(char)));
	while (ft_is_set(set, s1[end]))
		end--;
	new = ft_calloc(end - start + 2, sizeof(char));
	if (!new)
		return (0);
	i = 0;
	ft_strlcpy(new, &s1[start], end - start + 2);
	return (new);
}
