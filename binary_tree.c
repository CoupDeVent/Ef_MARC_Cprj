//
// Created by eytan on 11/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


t_node *create_node(t_node *father, t_move move, int score, t_localisation loc, int depth, int num_node){
    t_node *n = (t_node *)malloc(sizeof(t_node));

    n->father = father;
    n->children = (t_node **)malloc(9 * sizeof(t_node *));
    for(int k = 0; k < 9; k++){
        n->children[k] = NULL;
    }

    n->move = move;
    n->loc = loc;
    n->score = score;
    n->depth = depth;
    n->num_node = num_node;

    return n;
}

void print_tree(t_node *node, int depth){
    if(depth > 4){return;}
    if(depth == 0){
        printf("*-Rout-*\n");
    }

    for (int i = 0; i < 9 - depth; i++) {
        for (int k = 0; k < depth; k++) {
            printf("    ");
        }
        printf("%d |____*", node->depth);
        printf(" %d : %s : (x = %d, y = %d) : num = %d\n", node->children[i]->score, getMoveAsString(node->children[i]->move), node->children[i]->loc.pos.x, node->children[i]->loc.pos.y, node->children[i]->num_node);
        print_tree(node->children[i], depth + 1);

    }
}
