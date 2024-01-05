/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:43:25 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/05 14:51:05 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s.h"

char	*ft_strdup_s(const char *s1)
{
	char	*ret_str;

	ret_str = ft_strdup(s1);
	if (ret_str == NULL)
		btin_error();
	return (ret_str);
}
