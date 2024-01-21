/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:49:26 by michang           #+#    #+#             */
/*   Updated: 2024/01/21 15:49:27 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <dirent.h>

int	trtv_is_wild_matching(const char *pattern, const char *name)
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
	if (now == len_n)
		return (now == len_p);
	if (pattern[now] == '*')
	{
		skip = 0;
		while (skip + now <= len_n)
		{
			if (trtv_is_wild_matching(pattern + now + 1, name + skip + now))
				return (1);
			skip++;
		}
	}
	return (0);
}

int	main(void)
{
	char			*p;
	DIR				*d;
	struct dirent	*dir;

	printf("pattern: ");
	scanf("%s", p);
	printf("pattern=%s\n", p);
	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			printf("%s | is_matching:%d\n", dir->d_name, trtv_is_wild_matching(p, dir->d_name));
			dir = readdir(d);
		}
		closedir(d);
	}

	return (0);
}
