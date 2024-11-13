//
// Created by eytan on 11/11/2024.
//

#include "moves.h"
#include "loc.h"
#ifndef UNTITLED1_BINARY_TREE_H
#define UNTITLED1_BINARY_TREE_H

typedef struct s_node{
    struct s_node *father;
    struct s_node *left;
    struct s_node *right;

    t_move move;
    int score;
    t_orientation orientation;
} t_node;

typedef struct s_tree
{
    t_node *root;
} t_tree;

t_node *create_node(t_node *father,t_move move, int score, t_orientation orientation);

#endif //UNTITLED1_BINARY_TREE_H