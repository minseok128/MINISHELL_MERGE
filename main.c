/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:32:34 by seonjo            #+#    #+#             */
/*   Updated: 2024/01/04 21:02:08 by seonjo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_cmds	*ex_make_cmdsp()
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
	ex_add_cmdsp_node(cmdsp, argv, NULL, NULL);

	// pwd test
		// cmdsp->next->argv[0] = "pwd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);

	// env test
		// cmdsp->next->argv[0] = "env";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);

	// export & unset test
		// cmdsp->next->argv[0] = "export";
		// cmdsp->next->argv[1] = "test1=ls -l";
		// cmdsp->next->argv[2] = "test2=ls -al";
		// cmdsp->next->argv[3] = "1=100";
		// cmdsp->next->argv[4] = "test3=100";
		// cmdsp->next->argv[5] = "TEST=ls -l - a";
		// cmdsp->next->argv[6] = "p==23";
		// cmdsp->next->argv[7] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "env";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		
		// printf("\n\n\nunset\n\n\n");
		// cmdsp->next->argv[0] = "unset";
		// cmdsp->next->argv[1] = "test1";
		// cmdsp->next->argv[2] = "test2";
		// cmdsp->next->argv[3] = "1-7fdf";
		// cmdsp->next->argv[4] = "TEST";
		// cmdsp->next->argv[5] = "12c";
		// cmdsp->next->argv[6] = "p";
		// cmdsp->next->argv[7] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "env";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		
	// cd test
		// cmdsp->next->argv[0] = "cd";
		// cmdsp->next->argv[1] = "../pipex";
		// cmdsp->next->argv[2] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "pwd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "cd";
		// cmdsp->next->argv[1] = "../minishell";
		// cmdsp->next->argv[2] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "pwd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "cd";
		// cmdsp->next->argv[1] = "libft";
		// cmdsp->next->argv[2] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "pwd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "cd";
		// cmdsp->next->argv[1] = "../...";
		// cmdsp->next->argv[2] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "pwd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "cd";
		// cmdsp->next->argv[1] = "..";
		// cmdsp->next->argv[2] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "pwd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "cd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "pwd";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);
		
	// echo test
		// cmdsp->next->argv[0] = "echo";
		// cmdsp->next->argv[1] = "-nnn";
		// cmdsp->next->argv[2] = "-nnn";
		// cmdsp->next->argv[3] = "hi";
		// cmdsp->next->argv[4] = "-n";
		// cmdsp->next->argv[5] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "echo";
		// cmdsp->next->argv[1] = "good";
		// cmdsp->next->argv[2] = NULL;
		// ex_process_command(cmdsp, envsp);
		// cmdsp->next->argv[0] = "echo";
		// cmdsp->next->argv[1] = "-n";
		// cmdsp->next->argv[2] = "-nnnnnn";
		// cmdsp->next->argv[3] = "two";
		// cmdsp->next->argv[4] = NULL;
		// ex_process_command(cmdsp, envsp);

	// exit
		// cmdsp->next->argv[0] = "exit";
		// cmdsp->next->argv[1] = NULL;
		// ex_process_command(cmdsp, envsp);

}

// void command_test(t_envs *envp)
// {
// 	t_cmds	**cmdp;

// 	cmdp = malloc(sizeof(t_cmds *) * 2); 
// 	cmd = malloc(sizeof(t_cmds));
// 	cmd->argv = malloc(sizeof(char *) * 8);
// 	cmdp[1] = NULL;
// }

int	main(int argc, char **argv, char **envp)
{
	t_envs	*envsp;

	argv[argc - argc] = NULL;
	envsp = btin_make_envsp(envp);
	
	// builtin_test(envsp);
	// command_test(envsp);
	

	return (0);
}