/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:43:25 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/25 20:02:33 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft__strdup(const char *s1)
{
	char	*ret_str;
	
	ret_str = ft_strdup(s1);
	if (ret_str == NULL)
		builtin_error();
	return (ret_str);
}
