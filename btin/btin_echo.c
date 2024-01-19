/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:27:35 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 15:53:07 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	btin_is_option_n(char *str, int is_n_appear, int is_hyphen_appear)
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

void	btin_print_str(t_cmds *cmds, int i, int n_flag)
{
	if (cmds->argv.items[i + 1] == NULL)
	{
		ft_putstr_fd((char *)(cmds->argv.items[i]), 1);
		if (n_flag == 0)
			ft_putchar_fd('\n', 1);
	}
	else
	{
		ft_putstr_fd((char *)(cmds->argv.items[i]), 1);
		ft_putchar_fd(' ', 1);
	}
}

void	btin_echo(t_cmds *cmds, int fork_flag)
{
	int	i;
	int	n_flag;
	int	print_flag;

	i = 0;
	n_flag = 0;
	print_flag = 0;
	while (cmds->argv.items[++i] != NULL)
	{
		if (print_flag == 0 && btin_is_option_n(cmds->argv.items[i], 0, 0) == 1)
			n_flag = 1;
		else
		{
			btin_print_str(cmds, i, n_flag);
			print_flag = 1;
		}
	}
	btin_out(fork_flag, 0, NULL);
}
