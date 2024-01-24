/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:40:03 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/24 16:40:57 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ex_strjoin_c(char const *s1, char const *s2, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = ft_calloc_s(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = c;
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}
