/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:52:45 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/22 14:53:05 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl(int fd)
{
	int		flag;
	char	*line;

	flag = 0;
	line = get_next_line(fd, &flag);
	if (flag == 1)
		exit(1);
	return (line);
}