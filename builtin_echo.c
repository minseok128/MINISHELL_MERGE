/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:27:35 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/22 17:45:34 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option_n(char *str)
{
	int	i;
	int	hyphen;
	int	n;

	i = 0;
	hyphen = 0;
	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			hyphen = 1;
			if (n == 1)
				return (0);
		}
		else if (str[i] == 'n')
		{
			n = 1;
			if (hyphen == 0)
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

void	builtin_echo(t_cmd *cmd)
{
	int		i;
	int		n_flag;
	char	*str;

	errno = 0;
	n_flag = 0;
	i = 1;
	while (cmd->command[i] != NULL)
	{
		str = cmd->command[i];
		if (n_flag == 0 && is_option_n(str) == 1)
			n_flag = 1;
		else
			printf("%s", str);
		if (cmd->command[i + 1] == NULL && n_flag == 0)
			printf("\n");
		else if (cmd->command[i + 1] != NULL)
			printf(" ");
		i++;
	}
}
