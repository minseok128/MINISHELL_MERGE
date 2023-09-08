/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:48:11 by michang           #+#    #+#             */
/*   Updated: 2023/03/19 13:48:15 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*new;
	int		sign;

	size = ft_get_size(n);
	new = ft_calloc(size + 1, sizeof(char));
	if (!new)
		return (0);
	sign = 1;
	if (n < 0)
	{
		new[0] = '-';
		sign *= -1;
	}
	else if (n == 0)
		new[0] = '0';
	size--;
	while (n != 0)
	{
		new[size] = n % 10 * sign + '0';
		n /= 10;
		size--;
	}	
	return (new);
}
