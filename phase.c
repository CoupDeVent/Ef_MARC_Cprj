//
// Created by eytan on 11/11/2024.
//

#include "phase.h"
#include "binary_tree.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // pour rand
#include <intrin.h>

t_stat_game *init_stat_game(t_move *move_histo, int reach_base, t_node *min_node_tree){
    t_stat_game *stat_game = (t_stat_game*) malloc(sizeof(t_stat_game));

    stat_game->move_histo = (t_move *)malloc(6 * sizeof(t_move));
    for(int k = 0; k < 6; k++){
        stat_game->move_histo[k] = NONE;
    }

    memcpy(stat_game->move_histo, move_histo, 6 * sizeof(t_move));
    stat_game->reach_base = reach_base;
    stat_game->min_node_tree = min_node_tree;

    return stat_game;
}

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

t_stat_game *create_node_phase(t_move *nb_move_disp_phase, t_node *father, int depth, t_map map, t_localisation loc, t_move *move_histo, int num_node, t_stat_game *stat_game, int reg){
    if(depth > 5 - reg || stat_game->reach_base == 1){return stat_game;} // cas de base récur limit a 5 - reg (reg 1 si fini sur reg phase précédente) ou reach base True
    int score = COST_UNDEF; // score N.A

    for(int k = 0; k < 10 - depth; k++){
        move_histo[depth-1] = nb_move_disp_phase[num_node + k]; // remise zero move du node après modif temp_move_phase (après avoir deja utilisé dans un node du mm niveau avec mm père)
        // calcule pos post mov et si possible et score //
        t_localisation loc_node = move(loc, move_histo[depth-1]); // calcule loc post move
        if(isValidLocalisation(loc_node.pos, map.x_max, map.y_max) == 0){ // score = cost_undef si la loc n'est pas valide donc a l'exte de la map
            score = COST_UNDEF;
        }
        else if(map.costs[loc_node.pos.x][loc_node.pos.y] < 10000){
            score = map.costs[loc_node.pos.x][loc_node.pos.y]; // get score via map en parametre
        }
        else{score = COST_UNDEF;}

        // crea node et recur //
        if(score != COST_UNDEF){
            father->children[k] = create_node(father, move_histo[depth-1], score, loc_node, depth, num_node + k); // crea node actu

            if(father->children[k]->score == 0){
                stat_game->min_node_tree = father->children[k];
                memcpy(stat_game->move_histo, move_histo, 6 * sizeof(t_move));
                stat_game->reach_base = 1;
                return stat_game;
            }
            else if(father->children[k]->depth == 5 - reg && father->children[k]->score < stat_game->min_node_tree->score && father->children[k]->score > 0){ // bug cost sur les fonction donné
                stat_game->min_node_tree = father->children[k];
                memcpy(stat_game->move_histo, move_histo, 6 * sizeof(t_move));
            }

            stat_game = create_node_phase(nb_move_disp_phase, father->children[k], depth + 1, map, loc_node, move_histo, num_node + 1, stat_game, 0); // recur
        }
    }
    return stat_game;
}

t_tree *phase_tree(t_move *nb_move_disp_phase, t_map map, t_localisation rover_loc, int reg){
    t_move move_histo[6] = {NONE, NONE, NONE, NONE, NONE, NONE};

    /*
    printf("\n\nMove Phase :\n");
    for(int k = 0; k < 9; k++){
        printf("%s ", getMoveAsString(nb_move_disp_phase[k]));
    }
    printf("\n");
     */

    t_tree *phase_tree = (t_tree *)malloc(sizeof(t_tree));
    phase_tree->root = create_node(NULL, NONE, map.costs[rover_loc.pos.x][rover_loc.pos.y], rover_loc, 0, -1);

    t_node *false_node_temp = create_node(NULL, NONE, COST_UNDEF, rover_loc, 0, -1); // crea node temp pour stat_game
    phase_tree->stat_game = init_stat_game(move_histo, 0, false_node_temp);

    phase_tree->stat_game = create_node_phase(nb_move_disp_phase, phase_tree->root, 1, map, rover_loc, move_histo, 0, phase_tree->stat_game, reg);

    return phase_tree;
}


void game(char *map_name){
    char map_path[255] = "..\\maps\\";
    t_map map = createMapFromFile(strcat(map_path, map_name));
    printf("Map created with dimensions %d x %d :\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    printf("\nThe Costs :\n");
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    srand(time(NULL));
    t_localisation rover_loc = loc_init(rand()%map.x_max, rand()%map.y_max, rand()%4);
    while(map.costs[rover_loc.pos.x][rover_loc.pos.y] == 0 && map.costs[rover_loc.pos.x][rover_loc.pos.y] != COST_UNDEF && map.costs[rover_loc.pos.x][rover_loc.pos.y] < 10000){
        rover_loc = loc_init(rand()%map.x_max, rand()%map.y_max, rand()%4);
    }
    static char orientation[4][6] = {"NORTH", "EAST", "SOUTH", "WEST"};
    printf("\nRover start at : (x = %d  y = %d), %s", rover_loc.pos.x, rover_loc.pos.y, orientation[rover_loc.ori]);
    printf("\nThe Base is at : (x = %d  y = %d)", getBaseStationPosition(map).y, getBaseStationPosition(map).x);

    t_stat_game *stat_game;
    int reach_base = 0;
    int count = 0;
    t_move **move_game = (t_move **)malloc(255 * sizeof(t_move *));
    while(reach_base != 1){
        stat_game = phase_tree(getRandomMoves(9), map, rover_loc, 0)->stat_game;
        reach_base = stat_game->reach_base;
        rover_loc = stat_game->min_node_tree->loc;

        move_game[count] = stat_game->move_histo;
        count++;
    }
    printf("\n\n\nLe Rover a atteint la Base !");
    printf("\n    - En %d phases", count);
    printf("\n    - Avec les mouvements : ");
    for(int j = 0; j < count; j++){
        for(int k = 0; k < 6; k++){
            printf("%s ", getMoveAsString(move_game[j][k]));
        }
    }
    printf("\n");
    return;
}