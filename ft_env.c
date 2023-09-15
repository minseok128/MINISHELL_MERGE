/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:15:35 by seonjo            #+#    #+#             */
/*   Updated: 2023/09/15 18:11:04 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_and_exit(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

void	ft_env(t_envp *head)
{
	t_envp	*lst;

	if (head == NULL)
		return ;
	lst = head  -> next;
	while (lst != NULL)
	{
		printf("%s\n", lst -> str);
		lst = lst -> next;
	}
	// 마지막 줄 빼고 개행까지 diff로 비교 완료
	// _=/Users/seonjo/subjects/minishell/./a.out
	// _=/usr/bin/env
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*head;

	argv[argc - argc] = NULL;
	head = make_linkedlist(envp);
	//ft_pwd();
	//ft_env(head);
	//printf("\n\n");
	//ft_export(head, "a=1 a=3 b=2 17fdf=23 _17s= c=145124");
	//ft_env(head);
	//printf("\n\n");
	//ft_unset(head, "a b _17s 12");
	//ft_env(head);
	ft_cd("/Users/seonjo/subjects/minishell/libft");
	printf("%s\n", getcwd(NULL, 1024));
	exit(errno);
}
