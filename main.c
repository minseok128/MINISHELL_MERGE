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

	// pwd test 
		builtin_pwd();

	// env test
		builtin_env(envp_head);

	// export test
		cmd.command[1] = "a=1";
		cmd.command[2] = "b=3";
		cmd.command[3] = "17fdf=23";
		cmd.command[4] = "_17s=";
		cmd.command[5] = "c=145124";
		cmd.command[6] = "p = 23";
		cmd.command[7] = NULL;
		builtin_export(&cmd, envp_head);
		builtin_env(envp_head);

	// unset test
		// ex_export(head, "a=1 a=3 b=2 17fdf=23 _17s= c=145124");
		// un_unset(head, "a b _17s 12");
		// en_env(head);

	// cd test
		// cd_cd("");
		// pw_pwd();
		// cd_cd("..");
		// pw_pwd();
		// cd_cd("echo.c");
		// pw_pwd();
		// cd_cd("../..////////////..");
		// pw_pwd();
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