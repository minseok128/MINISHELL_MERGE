/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:43:00 by michang           #+#    #+#             */
/*   Updated: 2024/01/01 21:43:04 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../parser/parser.h"

static void print_node(t_tr_node *node, int flag)
{
    if (node->bnf_type == TR_LIST)
        printf("LIST ");
    if (node->bnf_type == TR_PIPELINE)
        printf("PIPE ");
    if (node->bnf_type == TR_COMMAND)
        printf("CMD  ");
    if (node->bnf_type == TR_COMMAND_PART)
        printf("%4s", node->tk->str);
    flag ? printf(" ") : printf("\n");
}

// 이진 트리를 중위 순회하는 함수
void inorderTraversal(t_tr_node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    print_node(root, 1);
    inorderTraversal(root->right);
}

// 터미널에 트리를 그리는 함수 (간단한 수준)
void printTree(t_tr_node* root, int space) {
    if (root == NULL) return;

    space += 5; // 간격 증가

    // 오른쪽 자식 먼저 출력
    printTree(root->right, space);
    printf("\n");

    for (int i = 5; i < space; i++)
        printf(" ");
    print_node(root, 0);

    // 왼쪽 자식 출력
    printTree(root->left, space);
}

int test_tr_print_tree(t_tr_node *root)
{
    // 트리 그리기
    printf("Tree Structure:\n");
    printTree(root, 0);

    return 0;
}


