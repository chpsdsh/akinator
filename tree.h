#ifndef TREEKINATOR_TREE_H
#define TREEKINATOR_TREE_H
#define TREE struct tree
#include <stdio.h>
#include <malloc.h>

TREE {
        int value;
        TREE *left, *right;
};


TREE* Create(int value) {
    TREE *res;
    res = (TREE*)malloc(sizeof(TREE));

    res -> value = value;
    res -> left = NULL;
    res -> right = NULL;

    return res;
}

void Insert(TREE *T, TREE *cur) {
    if (T -> value > cur -> value)
        if (T -> left == NULL)
            T -> left = cur;
        else
            Insert(T -> left, cur);
    else
    if (T -> right == NULL)
        T -> right = cur;
    else
        Insert(T -> right, cur);
}

int Search(int value, TREE *cur) {
    if (cur -> value == value)
        return 1;

    if (cur -> value > value)
        if (cur -> left == NULL)
            return 0;
        else
            Search(value, cur -> left);
    else
    if (cur -> right == NULL)
        return 0;
    else
        Search(value, cur -> right);
}

void PreOrder(TREE *T) {
    printf("%d", T -> value);

    if (T -> left != NULL)
        PreOrder(T -> left);
    if (T -> right != NULL)
        PreOrder(T -> right);
}

void PostOrder(TREE *T) {
    if (T -> left != NULL)
        PostOrder(T -> left);
    if (T -> right != NULL)
        PostOrder(T -> right);

    printf("%d", T -> value);
}

void InOrder(TREE *T) {
    if (T->left != NULL)
        InOrder(T->left);

    printf("%d", T->value);

    if (T->right != NULL)
        InOrder(T->right);
}

#endif //TREEKINATOR_TREE_H
