/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:11:16 by michang           #+#    #+#             */
/*   Updated: 2024/01/05 21:10:54 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_S_H
# define LIBFT_S_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "../libft/libft.h"

char	*ft_strdup_s(const char *s1);
void	*ft_calloc_s(size_t count, size_t size);

#endif
