/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:43:25 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/05 11:04:10 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft__strdup(const char *s1)
{
	char	*ret_str;

	ret_str = ft_strdup(s1);
	if (ret_str == NULL)
		btin_error();
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
		btin_error();
	while (s1[j])
		str[i++] = s1[j++];
	str[i++] = '=';
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*sign_check(char *str, long long *minus)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*minus = *minus * -1;
		str++;
	}
	return (str);
}

long long	overflow_check(long long num, long long i)
{
	if (i > 10)
		return (-1);
	if (num < 0 || num > 2147483647)
		return (-1);
	return (num);
}

long long	ft__atoi(char *str)
{
	long long	minus;
	long long	i;
	long long	num;

	i = 0;
	num = 0;
	minus = 1;
	while (*str >= 9 && *str <= 13)
		str++;
	str = sign_check(str, &minus);
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
		if (num > 0)
			i++;
	}
	if (*str != '\0')
		return (-1);
	return (overflow_check(num * minus, i));
}
