#include "minishell.h"

void    make_node(t_tree *node, char *str, int l, int r)
{
	node->str = str;
	if (l)
		node->left = malloc(sizeof(t_tree));
	else
		node->left = NULL;
	if (r)
		node->right = malloc(sizeof(t_tree));
	else
		node->right = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*envp_head;
	t_tree	*tree;
	t_fd	*fdp;

	argv[argc - argc] = NULL;
	envp_head = make_env(envp);

	fdp = malloc(sizeof(t_fd));
	fdp->next = NULL;

	tree = malloc(sizeof(t_tree));
	make_node(tree, "|", 1, 1);
	make_node(tree->left, "", 1, 1);
	make_node(tree->right, "", 0, 1);
	make_node(tree->left->left, "<", 0, 1);
	make_node(tree->left->right, "cat -s dfsfa", 0, 0);
	make_node(tree->left->left->right, "a", 0, 0);
	make_node(tree->right->right, "wc -l", 0, 0);
	tr_preorder(head, tree, fdp, 1);
}

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