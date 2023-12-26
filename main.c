#include "minishell.h"

// void    make_node(t_tree *node, char *str, int l, int r)
// {
// 	node->str = str;
// 	if (l)
// 		node->left = malloc(sizeof(t_tree));
// 	else
// 		node->left = NULL;
// 	if (r)
// 		node->right = malloc(sizeof(t_tree));
// 	else
// 		node->right = NULL;
// }

int	main(int argc, char **argv, char **envp)
{
	t_envp	*envp_head;
	t_cmd	cmd;

	argv[argc - argc] = NULL;
	envp_head = make_env(envp);

	cmd.command = malloc(sizeof(char *) * 8);
	if (cmd.command == NULL)
		return 1;

	// printf("\n\n\npwd test\n");
	// builtin_pwd();

	// printf("\n\n\nenv test\n");
	// builtin_env(envp_head);

	// printf("\n\n\nexport test\n");
	// cmd.command[1] = "test1=ls -l";
	// cmd.command[2] = "test2=ls -al";
	// cmd.command[3] = "1=100";
	// cmd.command[4] = "test3=100";
	// cmd.command[5] = "TEST=ls -l - a";
	// cmd.command[6] = "p==23";
	// cmd.command[7] = NULL;
	// builtin_export(&cmd, envp_head);
	// printf("\n\n");
	// builtin_env(envp_head);

	// printf("\n\n\nunset test\n");
	// cmd.command[1] = "a";
	// cmd.command[2] = "b";
	// cmd.command[3] = "1-7fdf";
	// cmd.command[4] = "_17s";
	// cmd.command[5] = "12c";
	// cmd.command[6] = "__p";
	// cmd.command[7] = NULL;
	// builtin_unset(&cmd, envp_head);
	// builtin_env(envp_head);

	// printf("\n\n\n cd test\n");
	// cmd.command[1] = NULL;
	// builtin_cd(&cmd, envp_head);
	// builtin_pwd();
	// cmd.command[1] = "..";
	// builtin_cd(&cmd, envp_head);
	// builtin_pwd();
	// cmd.command[1] = "libft";
	// builtin_cd(&cmd, envp_head);
	// builtin_pwd();
	// cmd.command[1] = "../......";
	// builtin_cd(&cmd, envp_head);
	// builtin_pwd();

	// printf("\n\n\n echo test\n");
	// cmd.command[1] = "-nnn";
	// cmd.command[2] = "-nnn";
	// cmd.command[3] = "hi";
	// cmd.command[4] = "-n";
	// cmd.command[5] = NULL;
	// builtin_echo(&cmd);
	// cmd.command[1] = "echo good";
	// cmd.command[2] = NULL;
	// builtin_echo(&cmd);
	// cmd.command[1] = "-n";
	// cmd.command[2] = "-nnnnn";
	// cmd.command[3] = "two";
	// cmd.command[4] = NULL;
	// builtin_echo(&cmd);

	return (0);
}
	// fdp = malloc(sizeof(t_fd));
	// fdp->next = NULL;

	// tree = malloc(sizeof(t_tree));
	// make_node(tree, "|", 1, 1);
	// make_node(tree->left, "", 1, 1);
	// make_node(tree->right, "", 0, 1);
	// make_node(tree->left->left, "<", 0, 1);
	// make_node(tree->left->right, "cat -s dfsfa", 0, 0);
	// make_node(tree->left->left->right, "a", 0, 0);
	// make_node(tree->right->right, "wc -l", 0, 0);
	// tr_preorder(head, tree, fdp, 1);