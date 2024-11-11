//
// Created by eytan on 11/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#define max(a,b) ((a)>(b)?(a):(b))

t_node *createNode(int val){
    t_node *n = (t_node *)malloc(sizeof(t_node));

    n -> value = val;
    n -> left = NULL;
    n -> right = NULL;

    return n;
}

int nodeHeight(t_node *n){
    if (n==NULL)
        return -1;

    int leftheight = nodeHeight(n->left);
    int rightheight = nodeHeight(n->right);
    return 1+max(leftheight,rightheight);
}

int nodeCount(t_node *pn){
    if (pn==NULL)
        return 0;

    int leftcount = nodeCount(pn->left);
    int rightcount = nodeCount(pn->right);
    return 1+leftcount+rightcount;
}