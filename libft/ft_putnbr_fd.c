/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:39:22 by seonjo            #+#    #+#             */
/*   Updated: 2023/03/19 16:57:55 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	n_print(long long num, int fd)
{
	char	c;

	if (num != 0)
	{
		n_print(num / 10, fd);
		c = num % 10 + '0';
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;
	int			minus;

	num = n;
	minus = 1;
	if (num == 0)
		write(fd, "0", 1);
	else
	{
		if (num < 0)
		{
			write(fd, "-", 1);
			num = -num;
		}
		n_print(num, fd);
	}
}
