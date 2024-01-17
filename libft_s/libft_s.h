/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_s.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 22:07:03 by michang           #+#    #+#             */
/*   Updated: 2024/01/17 14:50:44 by seonjo           ###   ########.fr       */
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
void	*ft_calloc_s(size_t count, size_t size);
char	*ft_strjoin_s(const char *s1, const char *s2);
void	vec_init(t_vector *v, int capacity);
void	vec_push_back(t_vector *v, void *item);
void	vec_free(t_vector *v);
void	vec_print(t_vector *v);

#endif