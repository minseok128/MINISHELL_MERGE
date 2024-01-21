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
		return (now == len_p);
	if (pattern[now] == '*')
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

	new_split = ft_calloc(sizeof(t_vector), 1);
	vec_init(new_split, 1);
	i = 0;
	while (i < (*word_split)->size)
	{
		d = opendir("./");
		if (d)
		{
			dir = readdir(d);
			while (dir)
			{
				printf("%s | is_matching:%d\n", dir->d_name, trtv_wcard_recursive(p, dir->d_name));
				dir = readdir(d);
			}
			closedir(d);
		}
		else

		i++;
	}
}
