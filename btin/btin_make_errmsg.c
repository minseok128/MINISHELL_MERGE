/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_make_errmsg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:14:57 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/17 16:50:05 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*btin_make_errmsg(char *s1, char *s2, char *s3)
{
	char	*merge1;
	char	*merge2;

	merge1 = ft_strjoin_s(s1, s2);
	merge2 = ft_strjoin_s(merge1, s3);
	free(merge1);
	return (merge2);
}
