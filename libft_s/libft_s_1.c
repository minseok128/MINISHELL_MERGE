/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:43:25 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/05 18:40:59 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s.h"

char	*ft_strdup_s(const char *s1)
{
	char	*ret_str;

	ret_str = ft_strdup(s1);
	if (ret_str == NULL)
	{
		printf("%s\n", strerror(errno));
		exit(errno);
	}
	return (ret_str);
}

void	*ft_calloc_s(size_t count, size_t size)
{
	void	*ret;

	ret = ft_calloc(count, size);
	if (ret = NULL)
	{
		printf("%s\n", strerror(errno));
		exit(errno);
	}
	return (ret);
}
