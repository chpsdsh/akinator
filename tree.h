#ifndef TREEKINATOR_TREE_H
#define TREEKINATOR_TREE_H
#define TREE struct tree
#include <stdio.h>
#include <malloc.h>

TREE {
        char* value;
        int nmb;
        TREE *left, *right;
};


TREE* create(char* value,int number) {
    TREE *res;
    res = (TREE*)malloc(sizeof(TREE));

    res -> value = value;
    res -> nmb = number;
    res -> left = NULL;
    res -> right = NULL;

    return res;
}

void add(TREE *T, char *value, int nmb){
    TREE *child;
    if(T != NULL)
    {
        if(T->nmb * 2 == nmb) {
            child = create(value,nmb);
            T->left = child;
        }
        else if(T->nmb * 2 + 1 == nmb) {
            child = create(value,nmb);
            T->right = child;
        }
        else{
            add(T->left,value,nmb);
            add(T->right,value,nmb);

        }
    }
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
    printf("%s\n", T -> value);

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
