/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:43:25 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 16:14:29 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft__strdup(const char *s1)
{
	char	*ret_str;

	ret_str = ft_strdup(s1);
	if (ret_str == NULL)
		builtin_error();
	return (ret_str);
}

char	*ft__strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 2);
	if (str == 0)
		builtin_error();
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = '=';
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}
