/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:43:14 by michang           #+#    #+#             */
/*   Updated: 2023/03/15 18:43:18 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				tmp;
	long long		result;
	int				sign;

	i = 0;
	while (ft_isspace(*(str + i)))
		i++;
	sign = 1;
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		tmp = *(str + i) - '0';
		result = result * 10 + tmp;
		i++;
	}
	return ((int)(result * sign));
}
