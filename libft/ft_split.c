/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:32:16 by michang           #+#    #+#             */
/*   Updated: 2023/03/19 13:32:17 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_word(char *str, char c)
{
	char	*word;
	int		i;
	int		size;

	size = 0;
	while (str[size] && str[size] != c)
		size++;
	word = (char *)ft_calloc(size + 1, sizeof(char));
	if (!word)
		return (0);
	i = 0;
	while (i < size)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	ft_get_size_of_arr(char *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			size++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (size);
}

static char	**ft_split_free(char **result, int arr_size)
{
	int	i;

	i = 0;
	while (i < arr_size)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static char	**ft_make_arr(char *str, char **result, char c, int arr_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == c)
			j++;
		else
		{
			result[i] = ft_get_word(&str[j], c);
			if (!result[i])
				return (ft_split_free(result, arr_size));
			i++;
			while (str[j] && str[j] != c)
				j++;
		}
	}
	return (result);
}

char	**ft_split(const char *str, char c)
{
	int		arr_size;
	char	**result;

	arr_size = ft_get_size_of_arr((char *)str, c) + 1;
	result = (char **)ft_calloc(arr_size, sizeof(char *));
	if (!result)
		return (0);
	return (ft_make_arr((char *)str, result, c, arr_size));
}
