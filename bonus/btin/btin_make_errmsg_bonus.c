/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_make_errmsg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:14:57 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/18 14:38:18 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

char	*btin_make_errmsg(char *s1, char *s2, char *s3)
{
	char	*merge1;
	char	*merge2;
	char	*merge3;

	merge1 = ft_strjoin_s(s1, s2);
	merge2 = ft_strjoin_s(merge1, ": ");
	merge3 = ft_strjoin_s(merge2, s3);
	free(merge1);
	free(merge2);
	return (merge3);
}
