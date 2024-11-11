//
// Created by eytan on 11/11/2024.
//

#ifndef UNTITLED1_BINARY_TREE_H
#define UNTITLED1_BINARY_TREE_H

typedef struct s_node{
    struct s_node *left;
    int value;
    struct s_node *right;
} t_node;

typedef struct s_tree
{
    t_node *root;
} t_tree;

t_node *createNode(int val);
int nodeHeight(t_node *n);
int nodeCount(t_node *pn);

#endif //UNTITLED1_BINARY_TREE_H