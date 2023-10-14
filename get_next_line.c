/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:02:39 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/13 17:28:50 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_size(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

void	renew_buffer(char *buffer, int size)
{
	int	i;

	i = 0;
	while (1)
	{
		buffer[i] = buffer[size];
		if (buffer[i] == '\0')
			break ;
		i = i + 1;
		size = size + 1;
	}
}

char	*ft_strnstr(char *pre, char *buffer, int size, size_t *dest_size)
{
	char	*dest;
	int		i;
	int		j;

	*dest_size = *dest_size + size;
	dest = (char *)malloc(sizeof(char) * (*dest_size + 1));
	if (dest == NULL)
		return (free_dest(pre));
	i = 0;
	while (pre[i] != '\0')
	{
		dest[i] = pre[i];
		i = i + 1;
	}
	j = 0;
	while (j < size)
	{
		dest[i] = buffer[j];
		i = i + 1;
		j = j + 1;
	}
	dest[i] = '\0';
	renew_buffer(buffer, size);
	free(pre);
	return (dest);
}

char	*make_dest(char *buffer, int fd, size_t dest_size)
{
	char	*dest;
	int		read_num;

	dest = (char *)malloc(sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[0] = '\0';
	if (buffer[0] != '\0')
		dest = ft_strnstr(dest, buffer, get_size(buffer), &dest_size);
	if (dest == NULL)
		return (NULL);
	while (dest[0] == '\0' || dest[dest_size - 1] != '\n')
	{
		read_num = read(fd, buffer, BUFFER_SIZE);
		if (read_num == -1)
			return (free_dest(dest));
		if (read_num == 0)
			break ;
		buffer[read_num] = '\0';
		dest = ft_strnstr(dest, buffer, get_size(buffer), &dest_size);
		if (dest == NULL)
			return (NULL);
	}
	return (dest);
}

char	*get_next_line(int fd, int *flag)
{
	static t_list2	*head;
	t_list2			*node;
	char			*dest;

	if (fd < 0)
		return (flag_set(flag));
	node = find_node(&head, fd);
	if (node == NULL)
		return (all_free(&head, flag));
	dest = make_dest(node -> buffer, fd, 0);
	if (dest == NULL)
	{
		(node -> buffer)[0] = '\0';
		flag_set(flag);
		return (remove_node(&head, fd));
	}
	if (dest[0] == '\0')
	{
		remove_node(&head, fd);
		return (free_dest(dest));
	}
	return (dest);
}
