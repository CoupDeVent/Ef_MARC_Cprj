//
// Created by eytan on 11/11/2024.
//

#ifndef UNTITLED1_PHASE_H
#define UNTITLED1_PHASE_H
#include "binary_tree.h"
#include "map.h"


// int *nb_move();
void create_node_phase(t_move *nb_move_disp_phase, t_node *father, int depth, t_map map, t_localisation loc, t_move *move_histo, int num_node);
t_tree* phase_tree(t_move *nb_move_disp_phase, t_map map, t_localisation rover_loc);
t_move *getRandomMoves(int N);
void game(t_map map)


#endif //UNTITLED1_PHASE_H
