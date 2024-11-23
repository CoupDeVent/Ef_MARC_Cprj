//
// Created by eytan on 11/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "phase.h"
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
        printf("\n*-Rout-*\n");
    }

    for (int i = 0; i < 9 - depth; i++) {
        if(node->children[i] != NULL){
            for (int k = 0; k < depth; k++) {
                printf("    ");
            }
            printf("%d |____*", node->depth);
            printf(" %d : %s : (x = %d, y = %d) : num = %d\n", node->children[i]->score, getMoveAsString(node->children[i]->move), node->children[i]->loc.pos.x, node->children[i]->loc.pos.y, node->children[i]->num_node);
            print_tree(node->children[i], depth + 1);
        }
    }
}

void print_stat_game(t_stat_game *stat_game){
    printf("\nstat_game print : \n    - moves :");
    for(int j = 0; j < 6; j++){
        printf(" %s", getMoveAsString(stat_game->move_histo[j]));
    }
    printf("\n    - reach_base : %d", stat_game->reach_base);
    printf("\n    - node (%d) : %d : %s : (x = %d, y = %d) : num = %d",stat_game->min_node_tree->depth, stat_game->min_node_tree->score, getMoveAsString(stat_game->min_node_tree->move), stat_game->min_node_tree->loc.pos.x, stat_game->min_node_tree->loc.pos.y, stat_game->min_node_tree->num_node);
    return;
}
