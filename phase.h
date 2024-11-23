//
// Created by eytan on 11/11/2024.
//

#ifndef UNTITLED1_PHASE_H
#define UNTITLED1_PHASE_H
#include "binary_tree.h"
#include "map.h"

t_stat_game *init_stat_game(t_move *move_histo, int reach_base, t_node *min_node_tree);
t_stat_game *create_node_phase(t_move *nb_move_disp_phase, t_node *father, int depth, t_map map, t_localisation loc, t_move *move_histo, int num_node, t_stat_game *stat_game, int reg);
t_tree *phase_tree(t_move *nb_move_disp_phase, t_map map, t_localisation rover_loc, int reg);
t_move *getRandomMoves(int N);
void game(char *map_name);


#endif //UNTITLED1_PHASE_H
