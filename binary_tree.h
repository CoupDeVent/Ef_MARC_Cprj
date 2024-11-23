//
// Created by eytan on 11/11/2024.
//
#ifndef UNTITLED1_BINARY_TREE_H
#define UNTITLED1_BINARY_TREE_H
#include "phase.h"
#include "moves.h"
#include "loc.h"

typedef struct s_node{
    struct s_node *father;
    struct s_node **children;

    t_move move;
    int score;
    t_localisation loc;
    int depth;
    int num_node;
} t_node;

typedef struct s_stat_game{
    t_move *move_histo;
    int reach_base;
    t_node *min_node_tree;
} t_stat_game;

typedef struct s_tree
{
    t_node *root;
    t_stat_game *stat_game;
} t_tree;

t_node *create_node(t_node *father, t_move move, int score, t_localisation loc, int depth, int num_node);
void print_tree(t_node *node, int depth);
void print_stat_game(t_stat_game *stat_game);

#endif //UNTITLED1_BINARY_TREE_H