/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:44 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 18:57:05 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	btin_pwd(int fork_flag)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (pwd == NULL)
		btin_error();
	printf("%s\n", pwd);
	free(pwd);
	btin_out(fork_flag, 0, NULL);
}
