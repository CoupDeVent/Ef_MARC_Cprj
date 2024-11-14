//
// Created by eytan on 11/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


t_node *create_node(t_node *father, t_move move, int score, t_orientation orientation){
    t_node *n = (t_node *)malloc(sizeof(t_node));

    n->father = father; // mais faire par queue
    n->left = NULL;
    n->right = NULL;

    n->move = move;
    n->score = score;
    n->orientation = orientation;

    return n;
}
