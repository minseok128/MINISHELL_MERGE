/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:44 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/22 17:04:38 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	*pwd;

	errno = 1;
	pwd = getcwd(NULL, 1024);
	if (pwd == NULL)
		builtin_error();
	printf("%s\n", pwd);
	free(pwd);
}
