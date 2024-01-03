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
#include <string.h>
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
        printf("%.4s", node->tk->str);
    flag ? printf(" ") : printf("\n");
}
void displayTree(t_tr_node *node, char *indent, int isLast) {
    if (node == NULL)
        return;

    printf("%s", indent);

    if (isLast) {
        printf("└─");
    } else {
        printf("├─");
    }

    // 노드 데이터 출력
    print_node(node, 0);

    // 들여쓰기 업데이트를 위한 새로운 임시 문자열
    char newIndent[1000];
    strcpy(newIndent, indent);
    if (isLast) {
        strcat(newIndent, "     ");  // 오른쪽 자식 (또는 자식 없음)을 위한 들여쓰기
    } else {
        strcat(newIndent, "│    ");  // 왼쪽 자식을 위한 들여쓰기
    }

    // 재귀적으로 자식 노드 출력
    displayTree(node->left, newIndent, node->right == NULL);
    displayTree(node->right, newIndent, 1);
}

int test_tr_print_tree(t_tr_node *root) {
    char indent[1000] = ""; // 초기 들여쓰기 설정
    displayTree(root, indent, 1); // 트리 출력

    return 0;
}