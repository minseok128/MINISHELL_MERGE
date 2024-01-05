/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 10:55:22 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/05 15:23:40 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	long long	i;
	long long	num;

	i = 0;
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
		if (num > 0)
			i++;
	}
	if (*str != '\0')
		return (-1);
	return (num * minus);
}

void	btin_out(int fork_flag, int error_code, char *errmsg)
{
	if (errmsg != NULL)
		printf("%s", errmsg);
	if (fork_flag == 1)
		exit(error_code);
	else
		g_errno = error_code;
}

void	btin_exit(t_cmds *cmds, int fork_flag)
{
	int	n;

	printf("exit\n");
	if (cmds->argv[1] == NULL)
		btin_out(1, 0, NULL);
	else
	{
		n = btin_atoi(cmds->argv[1]);
		if (n == -1)
		{
			printf("bash: exit: %s: numeric argument required\n", cmds->argv[1]);
			btin_out(1, 255, NULL);
		}
		else if (cmds->argv[2] != NULL)
			btin_out(fork_flag, 255, "bash: exit: too many arguments\n");
		else
			btin_out(1, (char)n, NULL);
	}
}
