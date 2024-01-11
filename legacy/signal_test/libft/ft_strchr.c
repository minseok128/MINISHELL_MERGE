/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:44:52 by michang           #+#    #+#             */
/*   Updated: 2023/03/15 18:44:54 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			new_c;
	char			*str;

	new_c = (char)c;
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == new_c)
			return (str + i);
		i++;
	}
	if (new_c == 0)
		return (str + i);
	return (0);
}
