/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:55:22 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/18 14:13:20 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*btin_sign_check(char *str, long long *minus)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*minus = *minus * -1;
		str++;
	}
	return (str);
}

long long	btin_is_overflow(long long num, int n, long long minus)
{
	if (minus == -1)
		n = n - 1;
	if (922337203685477580LL < num)
		return (1);
	if (9223372036854775807LL - num * 10 - n < 0)
		return (1);
	return (0);
}

long long	btin_atoi(char *str)
{
	long long	minus;
	long long	num;

	num = 0;
	minus = 1;
	while (*str >= 9 && *str <= 13)
		str++;
	str = btin_sign_check(str, &minus);
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		if (btin_is_overflow(num, *str - '0', minus) == 1)
			return (-1);
		num = num * 10 + *str - '0';
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (num * minus);
}

void	btin_out(int fork_flag, int error_code, char *errmsg)
{
	if (errmsg != NULL)
	{
		ft_putstr_fd(errmsg, 2);
		ft_putchar_fd('\n', 2);
		free(errmsg);
	}
	if (fork_flag == 1)
		exit(error_code);
	else
		g_errno = error_code;
}

void	btin_exit(t_cmds *cmds, int fork_flag)
{
	int	n;

	ft_putstr_fd("exit\n", 1);
	if (cmds->argv.items[1] == NULL)
		btin_out(1, 0, NULL);
	else
	{
		n = btin_atoi(cmds->argv.items[1]);
		if (n == -1)
		{
			btin_out(1, 255, btin_make_errmsg("minishell: exit: ", \
				(char *)cmds->argv.items[1], "numeric argument required"));
		}
		else if (cmds->argv.items[2] != NULL)
			btin_out(fork_flag, 1, btin_make_errmsg("minishell: ", \
				"exit", "too many arguments"));
		else
			btin_out(1, (char)n, NULL);
	}
}
