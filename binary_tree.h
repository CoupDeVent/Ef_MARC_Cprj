//
// Created by eytan on 11/11/2024.
//

#include "moves.h"
#include "loc.h"
#ifndef UNTITLED1_BINARY_TREE_H
#define UNTITLED1_BINARY_TREE_H

typedef struct s_node{
    struct s_node *father;
    struct s_node **children;

    t_move move;
    int score;
    t_localisation loc;
    int depth;
    int num_node;
} t_node;

typedef struct s_tree
{
    t_node *root;
} t_tree;

t_node *create_node(t_node *father, t_move move, int score, t_localisation loc, int depth, int num_node);
void print_tree(t_node *node, int depth);

#endif //UNTITLED1_BINARY_TREE_H