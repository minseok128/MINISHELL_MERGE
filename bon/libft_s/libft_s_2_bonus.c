/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:07:03 by michang           #+#    #+#             */
/*   Updated: 2024/01/26 20:30:34 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*ft_strjoin_s(const char *s1, const char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (!new)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"malloc", strerror(errno)), NULL);
	return (new);
}

char	*ft_strchr_s(const char *s, int c)
{
	if (!s)
		return (0);
	return (ft_strchr(s, c));
}

char	**ft_split_s(const char *str, char c)
{
	char	**new;

	new = ft_split(str, c);
	if (!new)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"malloc", strerror(errno)), NULL);
	return (new);
}

int	ft_jump_white_space(char *str)
{
	while (*str)
	{
		if (*str != 32 && !(*str >= 9 && *str <= 13))
			return (0);
		str++;
	}
	return (1);
}
