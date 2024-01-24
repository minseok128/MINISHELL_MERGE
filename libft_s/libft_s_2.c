/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:07:03 by michang           #+#    #+#             */
/*   Updated: 2024/01/18 14:19:40 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_s(const char *s1, const char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (!new)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"malloc", strerror(errno)));
	return (new);
}

char	*ft_strchr_s(const char *s, int c)
{
	if (!s)
		return (0);
	return (ft_strchr(s, c));
}
