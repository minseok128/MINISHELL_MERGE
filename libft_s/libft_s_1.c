/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:07:03 by michang           #+#    #+#             */
/*   Updated: 2023/03/18 22:07:09 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s.h"

char	*ft_substr_s(char const *s, unsigned int start, size_t len)
{
	char	*new;
	new = ft_substr(s, start, len);
	if (!new)
		exit(1);
	return (new);
}
