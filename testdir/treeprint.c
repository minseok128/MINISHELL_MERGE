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

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// 노드 생성 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 이진 트리를 중위 순회하는 함수
void inorderTraversal(Node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// 터미널에 트리를 그리는 함수 (간단한 수준)
void printTree(Node* root, int space) {
    if (root == NULL) return;

    space += 5; // 간격 증가

    // 오른쪽 자식 먼저 출력
    printTree(root->right, space);
    printf("\n");

    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    // 왼쪽 자식 출력
    printTree(root->left, space);
}

// 트리 메모리 해제 함수
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // 트리 예시 생성
    Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // 중위 순회 출력
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n\n");

    // 트리 그리기
    printf("Tree Structure:\n");
    printTree(root, 0);

    // 메모리 해제
    freeTree(root);
    return 0;
}


