//
// Created by eytan on 11/11/2024.
//

#include "phase.h"
#include "binary_tree.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // pour rand

t_move *getRandomMoves(int N){
    int nbmoves[]={22,15,7,7,21,21,7};
    int total_moves=100;
    t_move *moves = (t_move *)malloc(N * sizeof(t_move));
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        int r = rand() % total_moves;
        int type=0;
        while (r >= nbmoves[type])
        {
            r -= nbmoves[type];
            type++;
        }
        nbmoves[type]--;
        total_moves--;
        moves[i] = (t_move )type;
    }
    return moves;
}

void create_node_phase(t_move *nb_move_disp_phase, t_node *father, int depth, t_map map, t_localisation loc, t_move *move_histo, int num_node){
    if(depth > 5){return;} // cas de base récur limit a 5
    int score = COST_UNDEF; // score N.A

    for(int k = 0; k < 10 - depth; k++){
        move_histo[depth-1] = nb_move_disp_phase[num_node + k]; // remise zero move du node après modif temp_move_phase (après avoir deja utilisé dans un node du mm niveau avec mm père)
        // calcule pos post mov et si possible et score //
        t_localisation loc_node = move(loc, move_histo[depth-1]); // calcule loc post move
        if(isValidLocalisation(loc_node.pos, map.x_max, map.y_max) == 0){ // score = 10999 si la loc n'est pas valide donc a l'exte de la map
            score = COST_UNDEF;
        }
        else{
            score = map.costs[loc_node.pos.x][loc_node.pos.y]; // get score via map en parametre
        }

        // crea node et recur //
        father->children[k] = create_node(father, move_histo[depth-1], score, loc_node, depth, num_node + k); // crea node actu
        create_node_phase(nb_move_disp_phase, father->children[k], depth + 1, map, loc_node, move_histo, num_node + 1); // recur
    }
}

t_tree *phase_tree(t_move *nb_move_disp_phase, t_map map, t_localisation rover_loc){
    t_move move_histo[6] = {NONE, NONE, NONE, NONE, NONE, NONE};

    printf("\nMove Phase :\n");
    for(int k = 0; k < 9; k++){
        printf("%s ", getMoveAsString(nb_move_disp_phase[k]));
    }
    printf("\n");

    t_tree *phase_tree = (t_tree *)malloc(sizeof(t_tree));
    phase_tree->root = create_node(NULL, NONE, map.costs[rover_loc.pos.x][rover_loc.pos.y], rover_loc, 0, -1);

    create_node_phase(nb_move_disp_phase, phase_tree->root, 1, map, rover_loc, move_histo, 0);

    return phase_tree;
}

void game(t_map map){
    srand(time(NULL));
    t_localisation rover_loc = loc_init(rand()%map.x_max, rand()%map.y_max, rand()%4);
    while(map.costs[rover_loc.pos.x][rover_loc.pos.y] == 0){
        rover_loc = loc_init(rand()%map.x_max, rand()%map.y_max, rand()%4);
    }

    int reach_base = 0;
    while(reach_base != 1){
        reach_base = phase_tree(nb_move(), map, rover_loc);
    }
}