/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:25:10 by seonjo            #+#    #+#             */
/*   Updated: 2023/10/09 20:14:07 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	en_env(t_envp *head)
{
	t_envp	*lst;

	if (head == NULL)
		return ;
	lst = head->next;
	while (lst != NULL)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	// 마지막 줄 빼고 개행까지 diff로 비교 완료
	// _=/Users/seonjo/subjects/minishell/./a.out
	// _=/usr/bin/env
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*head;

	argv[argc - argc] = NULL;
	head = en_divide_key_and_value(envp);
	
	//pwd test 
		//pw_pwd();
	
	//env test
		//en_env(head);

	//export test
		//ex_export(head, "a=1 a=3 b=2 17fdf=23 _17s= c=145124");
		//en_env(head);

	//unset test
		//ex_export(head, "a=1 a=3 b=2 17fdf=23 _17s= c=145124");
		//un_unset(head, "a b _17s 12");
		//en_env(head);

	//cd test
		//cd_cd("");
		//pw_pwd();
		//cd_cd("..");
		//pw_pwd();
		//cd_cd("echo.c");
		//pw_pwd();
		//cd_cd("../..////////////..");
		//pw_pwd();
	exit(errno);
}