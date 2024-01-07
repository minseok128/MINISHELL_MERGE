/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:28:16 by michang           #+#    #+#             */
/*   Updated: 2024/01/07 18:28:17 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_s.h"

void	vec_init(t_vector *v, int capacity)
{
	v->capacity = capacity;
	v->size = 0;
	v->items = ft_calloc_s(sizeof(void *), capacity);
}

void	vec_push_back(t_vector *v, void *item)
{
	void	**prev_items;
	void	**items;
	int		i;

	if (v->size == v->capacity)
	{
		items = ft_calloc_s(sizeof(void *), v->capacity * 2);
		i = 0;
		while (i < v->capacity)
		{
			items[i] = v->items[i];
			i++;
		}
		prev_items = v->items;
		v->items = items;
		v->capacity = v->capacity * 2;
		free(prev_items);
	}
	v->items[v->size++] = item;
}

void	vec_print(t_vector *v)
{
	int	i;

	i = 0;
	while (i < v->size)
		printf("%s\n", v->items[i++]);
}

void	vec_free(t_vector *v)
{
	free(v->items);
}
