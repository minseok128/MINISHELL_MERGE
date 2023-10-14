/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:08:01 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/22 14:53:17 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

typedef struct s_list2
{
	int				fd;
	char			buffer[BUFFER_SIZE + 1];
	struct s_list2	*next;
}t_list2;

char	*ft_gnl(int fd);
char	*get_next_line(int fd, int *flag);
void	*all_free(t_list2 **head, int *flag);
void	*free_dest(char *dest);
void	*flag_set(int *flag);
void	*remove_node(t_list2 **head, int fd);
t_list2	*find_node(t_list2 **head, int fd);

#endif