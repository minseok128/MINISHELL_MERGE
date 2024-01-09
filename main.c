/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:32:34 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/09 18:54:07 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*ex_make_cmdsp(void)
{
	t_cmds	*cmdsp_head;

	cmdsp_head = malloc(sizeof(t_cmds));
	if (cmdsp_head == NULL)
		exit(0);
	cmdsp_head->next = NULL;
	return (cmdsp_head);
}

void	ex_add_cmdsp_node(t_cmds *cmdsp, char **argv, char *in, char *out)
{
	t_cmds	*new;
	t_cmds	*node;

	new = malloc(sizeof(t_cmds));
	if (new == NULL)
		exit(0);
	new->argv = argv;
	new->in_file = in;
	new->out_file = out;
	new->next = NULL;
	node = cmdsp;
	while(node->next != NULL)
		node = node->next;
	node->next = new;
}

void builtin_test(t_envs *envsp)
{
	t_cmds	*cmdsp;
	char	**argv;

	cmdsp = ex_make_cmdsp();
	argv = malloc(sizeof(char *) * 8);
	ex_add_cmdsp_node(cmdsp, argv, 0, 0);

	// pwd test       << no leak
		cmdsp->next->argv[0] = "pwd";
		cmdsp->next->argv[1] = NULL;
		ex_process_command(cmdsp, envsp);

	// env test       << no leak
		// cmdsp->next->argv[0] = "env";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);

	// export & unset test
		// printf("export\n");
		// cmdsp->next->argv[0] = "export";
		// cmdsp->next->argv[1] = "test1=ls -l";
		// cmdsp->next->argv[2] = "test2=";
		// cmdsp->next->argv[3] = "1=100";
		// cmdsp->next->argv[4] = "test3";
		// cmdsp->next->argv[5] = "TEST=ls -l - a";
		// cmdsp->next->argv[6] = "p==23";
		// cmdsp->next->argv[7] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "env";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);

		// printf("\n\nexport -no arg\n");
		// cmdsp->next->argv[0] = "export";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		
		// printf("\n\n\nunset\n");
		// cmdsp->next->argv[0] = "unset";
		// cmdsp->next->argv[1] = "test1";
		// cmdsp->next->argv[2] = "test2";
		// cmdsp->next->argv[3] = "test34";
		// cmdsp->next->argv[4] = "TEST";
		// cmdsp->next->argv[5] = "12c";
		// cmdsp->next->argv[6] = "p";
		// cmdsp->next->argv[7] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "env";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);

		// printf("\n\nexport -no arg\n");
		// cmdsp->next->argv[0] = "export";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		
	// cd test         << no leak
		// cmdsp->next->argv[0] = "cd";
		// cmdsp->next->argv[1] = "test";
		// cmdsp->next->argv[2] = NULL;
		// ex_process_command(cmdsp, envsp);
		// printf("errno : %d\n", g_errno);
		// cmdsp->next->argv[0] = "pwd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		
	// echo test           << no leak
		// cmdsp->next->argv[0] = "echo";
		// cmdsp->next->argv[1] = "-n-nn";
		// cmdsp->next->argv[2] = "-nnn";
		// cmdsp->next->argv[3] = "hi";
		// cmdsp->next->argv[4] = "-n";
		// cmdsp->next->argv[5] = NULL;
		// ex_process_command(cmdsp, envsp);

	// exit test              << no leak
		// cmdsp->next->argv[0] = "exit";
		// cmdsp->next->argv[1] = "1s";
		// cmdsp->next->argv[2] = NULL;
		// ex_process_command(cmdsp, envsp);

	free(cmdsp->next->argv);
	free(cmdsp->next);
	free(cmdsp);
}

void command_test(t_envs *envsp)
{
	t_cmds	*cmdsp;

	cmdsp = ex_make_cmdsp();
	char **argv1 = malloc(sizeof(char *) * 100);
	char **argv2 = malloc(sizeof(char *) * 100);
	argv1[0] = "cat";
	argv1[1] = NULL;
	ex_add_cmdsp_node(cmdsp, argv1, "a", NULL);
	argv2[0] = "wc";
	argv2[1] = "-l";
	argv2[2] = NULL;
	ex_add_cmdsp_node(cmdsp, argv2, NULL, NULL);
	ex_process_command(cmdsp, envsp);
}

// void	leak_check()
// {
// 	system("leaks minishell");
// }

void	envs_free(t_envs *envsp)
{
	t_envs	*tmp;
	t_envs	*tmp2;

	tmp = envsp->next;
	while (tmp != NULL)
	{
		if (tmp->key != NULL)
			free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	free(envsp);
}

int	main(int argc, char **argv, char **envp)
{
	t_envs	*envsp;

	argv[argc - argc] = NULL;
	envsp = btin_make_envsp(envp);

	// builtin_test(envsp);
	command_test(envsp);

	envs_free(envsp);
	// atexit(leak_check);
	return (g_errno);
}