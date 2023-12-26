/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:27:35 by seonjo            #+#    #+#             */
/*   Updated: 2023/12/26 17:12:36 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option_n(char *str, int is_n_appear, int is_hyphen_appear)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			if (is_hyphen_appear == 1 || is_n_appear == 1)
				return (0);
			is_hyphen_appear = 1;
		}
		else if (str[i] == 'n')
		{
			if (is_hyphen_appear == 0)
				return (0);
			is_n_appear = 1;
		}
		else
			return (0);
		i++;
	}
	if (is_n_appear == 1 && is_hyphen_appear == 1)
		return (1);
	else
		return (0);
}

void	builtin_echo(t_cmd *cmd)
{
	int		i;
	int		n_flag;
	int		print_flag;
	char	*str;

	errno = 0;
	n_flag = 0;
	print_flag = 0;
	i = 1;
	while (cmd->command[i] != NULL)
	{
		str = cmd->command[i];
		if (print_flag == 0 && is_option_n(str, 0, 0) == 1)
			n_flag = 1;
		else if (cmd->command[i + 1] == NULL)
		{
			if (n_flag == 1)
				printf("%s", str);
			else
				printf("%s\n", str);
		}
		else
		{
			printf("%s ", str);
			print_flag = 1;
		}
		i++;
	}
}
