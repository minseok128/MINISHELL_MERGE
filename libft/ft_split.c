/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:24:46 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/22 14:43:17 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_str_num(char const *s, char c, size_t j, int opt)
{
	size_t	n;
	size_t	i;

	if (opt == 0)
	{
		i = 0;
		n = 0;
		while (s[i])
		{
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
				n++;
			i++;
		}
		return (n);
	}
	else
	{
		while (s[j] == c)
			j++;
		return (j);
	}
}

static int	fill_arr(char *arr, char const *s, char c, size_t j)
{
	size_t	i;

	i = 0;
	while (s[j] != c && s[j])
		arr[i++] = s[j++];
	arr[i] = 0;
	return (j);
}

static size_t	get_len(char const *s, char c, size_t j)
{
	size_t	len;

	len = 0;
	while (s[j] != c && s[j])
	{
		j++;
		len++;
	}
	return (len);
}

static char	**allfree(char **arr, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
		free(arr[j++]);
	free(arr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	num;
	size_t	i;
	size_t	j;
	char	**arr;

	i = 0;
	j = 0;
	num = find_str_num(s, c, j, 0);
	arr = ft_calloc(sizeof(char *), num + 1);
	if (arr == 0)
		return (0);
	while (i < num)
	{
		j = find_str_num(s, c, j, 1);
		if (s[j] == 0)
			break ;
		arr[i] = ft_calloc(sizeof(char), get_len(s, c, j) + 1);
		if (arr[i] == 0)
			return (allfree(arr, i));
		j = fill_arr(arr[i++], s, c, j);
	}
	arr[i] = 0;
	return (arr);
}
