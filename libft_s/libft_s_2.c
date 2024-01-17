/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:07:03 by michang           #+#    #+#             */
/*   Updated: 2024/01/17 18:28:25 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s.h"

char	*ft_strjoin_s(const char *s1, const char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (!new)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"malloc: ", strerror(errno)));
	return (new);
}
