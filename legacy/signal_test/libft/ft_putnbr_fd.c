/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:48:26 by michang           #+#    #+#             */
/*   Updated: 2023/03/19 14:48:28 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(int nb, int sign, int fd)
{
	char	c;

	if (!nb)
		return ;
	ft_recursive(nb / 10, sign, fd);
	c = nb % 10 * sign + '0';
	ft_putchar_fd(c, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (!n)
		ft_putchar_fd('0', fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_recursive(n, -1, fd);
	}
	else
		ft_recursive(n, 1, fd);
}
