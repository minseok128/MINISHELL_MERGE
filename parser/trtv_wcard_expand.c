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

void	trtv_wcard_get(DIR *d, t_vector *new_split, char *pattern)
{
	struct dirent	*dir;
	int				mode;
	char			*new_name;

	mode = 0;
	mode |= (pattern[0] == '.');
	mode |= (pattern[ft_strlen(pattern) - 1] == '/') * 2;
	dir = readdir(d);
	while (dir)
	{
		if (trtv_wcard_recursive(pattern, dir->d_name))
		{
			new_name = 0;
			if (((mode & 1) && dir->d_name[0] == '.')
				|| (!(mode & 1) && dir->d_name[0] != '.'))
				new_name = ft_strdup_s(dir->d_name);
			if (new_name && mode & 2)
			{
				free(new_name);
				new_name = 0;
				if (dir->d_type == DT_DIR)
					new_name = ft_strjoin_s(dir->d_name, "/");
			}
			if (new_name)
				vec_push_back(new_split, new_name);
		}
		dir = readdir(d);
	}
}

void	trtv_wcard_expand(t_vector **word_split)
{
	DIR				*d;
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
			trtv_wcard_get(d, new_split, (*word_split)->items[i]);
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
