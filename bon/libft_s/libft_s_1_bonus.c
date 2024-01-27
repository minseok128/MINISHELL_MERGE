/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s_1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:07:03 by michang           #+#    #+#             */
/*   Updated: 2024/01/26 20:07:05 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

char	*ft_substr_s(char const *s, unsigned int start, size_t len)
{
	char	*new;

	new = ft_substr(s, start, len);
	if (!new)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"malloc", strerror(errno)), NULL);
	return (new);
}

char	*ft_itoa_s(int n)
{
	char	*new;

	new = ft_itoa(n);
	if (!new)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"malloc", strerror(errno)), NULL);
	return (new);
}

char	*ft_strdup_s(const char *s1)
{
	char	*new;

	new = ft_strdup(s1);
	if (!new)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"malloc", strerror(errno)), NULL);
	return (new);
}

void	*ft_calloc_s(size_t count, size_t size)
{
	void	*new;

	new = ft_calloc(count, size);
	if (!new)
		btin_out(1, errno, btin_make_errmsg("minishell: ", \
			"malloc", strerror(errno)), NULL);
	return (new);
}
