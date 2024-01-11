/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:07:03 by michang           #+#    #+#             */
/*   Updated: 2023/03/18 22:07:09 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_S_H
# define LIBFT_S_H
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_vector {
	void	**items;
	int		capacity;
	int		size;
}	t_vector;

int		ft_isspace(char c);
char	*ft_substr_s(char const *s, unsigned int start, size_t len);
char	*ft_itoa_s(int n);
char	*ft_strdup_s(const char *s1);
void	vec_init(t_vector *v, int capacity);
void	vec_push_back(t_vector *v, void *item);
void	vec_free(t_vector *v);
void	vec_print(t_vector *v);

#endif