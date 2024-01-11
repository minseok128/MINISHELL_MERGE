/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:45:38 by michang           #+#    #+#             */
/*   Updated: 2024/01/05 20:50:36 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (0);
	i = 0;
	while (i < len)
	{
		new[i] = s1[i];
		i++;
	}
	return (new);
}

char	*ft_strdup_s(const char *s1)
{
	char	*new;
	size_t	i;
	size_t	len;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		exit(1);
	i = 0;
	while (i < len)
	{
		new[i] = s1[i];
		i++;
	}
	return (new);
}
