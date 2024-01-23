/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trtv_wcard_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:18:08 by michang           #+#    #+#             */
/*   Updated: 2024/01/21 17:18:09 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trtv_wcard_recursive(const char *pattern, const char *name)
{
	int	len_p;
	int	len_n;
	int	now;
	int	skip;

	len_p = strlen(pattern);
	len_n = strlen(name);
	now = 0;
	while (now < len_p && now < len_n && pattern[now] == name[now])
		now++;
	if (now == len_p)
		return (now == len_n);
	if (pattern[now] == 6)
	{
		skip = 0;
		while (skip + now <= len_n)
		{
			if (trtv_wcard_recursive(&pattern[now + 1], &name[skip + now]))
				return (1);
			skip++;
		}
	}
	return (0);
}

void	trtv_wcard_expand(t_vector **word_split)
{
	DIR				*d;
	struct dirent	*dir;
	t_vector		*new_split;
	int				i;
	unsigned int	j;

	new_split = ft_calloc(sizeof(t_vector), 1);
	vec_init(new_split, 1);
	i = 0;
	while (i < (*word_split)->size)
	{
		d = opendir("./");
		if (d && ft_strchr((*word_split)->items[i], 6))
		{
			dir = readdir(d);
			while (dir)
			{
				if (trtv_wcard_recursive((*word_split)->items[i], dir->d_name))
				{
					if (*((char *)((*word_split)->items[i])) == '.' && dir->d_name[0] == '.')
						vec_push_back(new_split, ft_strdup_s(dir->d_name));
					else if (dir->d_name[0] != '.')
						vec_push_back(new_split, ft_strdup_s(dir->d_name));
				}
				dir = readdir(d);
			}
		}
		if (!d || new_split->size == 0)
		{
			if (ft_strchr((*word_split)->items[i], 6))
			{
				j = 0;
				while (j < ft_strlen((*word_split)->items[i]))
				{
					if (((char *)((*word_split)->items[i]))[j] == 6)
						((char *)((*word_split)->items[i]))[j] = '*';
					j++;
				}
			}
			vec_push_back(new_split, ft_strdup_s((*word_split)->items[i]));
		}
		closedir(d);
		free((*word_split)->items[i]);
		i++;
	}
	vec_free(*word_split);
	free(*word_split);
	*word_split = new_split;
}
