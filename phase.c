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

/**
 * @brief Init for the t_stat_struct
 * @param *move_histo : The history of movements leading to the node
 * @param reach_base : Bool variable, TRUE (1) if the node is on the base (score = 0) / FALSE (0) else
 * @param *min_node_tree : The current minimum node of the tree
 * @return stat_game
 */
t_stat_game *init_stat_game(t_move *move_histo, int reach_base, t_node *min_node_tree){
    t_stat_game *stat_game = (t_stat_game*) malloc(sizeof(t_stat_game));

    stat_game->move_histo = (t_move *)malloc(6 * sizeof(t_move));
    if(stat_game->move_histo == NULL){printf("Allocation error for the stat_game in the init_stat_game function");return NULL;} // Allocation error, error message
    for(int k = 0; k < 6; k++){
        stat_game->move_histo[k] = NONE;
    }

    memcpy(stat_game->move_histo, move_histo, 6 * sizeof(t_move));
    stat_game->reach_base = reach_base;
    stat_game->min_node_tree = min_node_tree;

    return stat_game;
}

/**
 * @brief Get N random move based on the nbmove variable
 * @param *N : The number of move that we need for our phase (case reg or not => 5 or 4)
 * @return moves, a t_move list of the move for our phase
 * (made by Flasque)
 */
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

/**
 * @brief the recursive function to creat our Tree (for each phase)
 * @param *nb_move_disp_phase : the list of the movement that are available for our phase
 * @param *father : the father (t_node) of our current node
 * @param depth : the depth of the node
 * @param map : the map
 * @param loc : the localisation of the father that are updated to become the actual node localisation
 * @param *move_histo : the historic of the moves that lead to the current node
 * @param num_node : the number of the node, this is the number associated with its index of father->children (use in debug)
 * @param *stat_game : its where the node with the minimum score are stock and other information for the game in general
 * @param reg : bool, TRUE (1) if the last phase ended on a reg / FALSE (0) else
 * @return stat_game with all the information about the phase and the best moves to do
 */
t_stat_game *create_node_phase(t_move *nb_move_disp_phase, t_node *father, int depth, t_map map, t_localisation loc, t_move *move_histo, int num_node, t_stat_game *stat_game, int reg){
    if(depth > 5 - reg || stat_game->reach_base == 1){return stat_game;} // basic case of recursion, if depth > 5 - reg or if we reach the base before the end
    int score = COST_UNDEF; // score N.A

    for(int k = 0; k < 10 - depth; k++){
        move_histo[depth-1] = nb_move_disp_phase[num_node + k]; // reset of move_histo[depth-1] who are the current move

        // calculation of the new location of the node after the movement and if it's valid //
        t_localisation loc_node = move(loc, move_histo[depth-1]);
        if(isValidLocalisation(loc_node.pos, map.x_max, map.y_max) == 0){ // if == 0 (FALSE) the movement of the node are not valid => score = COST_UNDEF
            score = COST_UNDEF;
        }
        else if(map.costs[loc_node.pos.x][loc_node.pos.y] < 10000){ // if its a valid move (bypass the reg) => score = cost
            score = map.costs[loc_node.pos.x][loc_node.pos.y];
        }
        else{score = COST_UNDEF;}

        // creation of the node and recursion //
        if(score != COST_UNDEF && depth <= 5 - reg){ // if the score are valid we create the node, else not
            father->children[k] = create_node(father, move_histo[depth-1], score, loc_node, depth, num_node + k); // creation of the node

            if(father->children[k]->score == 0){ // if score == 0 its means that we reach the base so end of the recursion and actualisation of stat_game
                stat_game->min_node_tree = father->children[k]; // stat_game take the current node (that are on the base)
                memcpy(stat_game->move_histo, move_histo, 6 * sizeof(t_move)); // cpy the moves that lead to it (move_histo)
                stat_game->reach_base = 1; // update the bool variable to 1
                return stat_game;
            }
            else if(father->children[k]->depth == 5 - reg && // if the node are at the good depth (5 - reg)
                    father->children[k]->score < stat_game->min_node_tree->score && // and if its score (cost) are < of the current node stock in stat_game
                    father->children[k]->score > 0){ // and if its score are valid (>0)

                stat_game->min_node_tree = father->children[k]; // update stat_game
                memcpy(stat_game->move_histo, move_histo, 6 * sizeof(t_move)); // and cpy the moves that lead to it (move_histo) and continue the recursion and the creation of the tree
            }

            // recursion call with the updated variables //
            stat_game = create_node_phase(nb_move_disp_phase, father->children[k], depth + 1, map, loc_node, move_histo, num_node + 1, stat_game, 0);
        }
    }
    return stat_game;
}

/**
 * @brief the function that brings together all the information about the tree and the tree itself
 * @param *nb_move_disp_phase : all the movement that are avaliable for the phase
 * @param map : the map
 * @param rover_loc : the localisation of the rover
 * @param reg : bool, TRUE (1) if the last phase ended on a reg / FALSE (0) else
 * @return phase_tree a struct with the root of the tree and the struct t_stat_game
 */
t_tree *phase_tree(t_move *nb_move_disp_phase, t_map map, t_localisation rover_loc, int reg){
    t_move move_histo[6] = {NONE, NONE, NONE, NONE, NONE, NONE};

    /* // debug option to see the move avaliable for the phase //
    printf("\n\nMove Phase :\n");
    for(int k = 0; k < 9; k++){
        printf("%s ", getMoveAsString(nb_move_disp_phase[k]));
    }
    printf("\n");
     */

    t_tree *phase_tree = (t_tree *)malloc(sizeof(t_tree)); // creation of the tree
    if(phase_tree == NULL){printf("Allocation error of phase_tree in the function phase_tree");return NULL;} // allocation error security

    phase_tree->root = create_node(NULL, NONE, map.costs[rover_loc.pos.x][rover_loc.pos.y], rover_loc, 0, -1); // creation of the root at the rover location

    t_node *false_node_temp = create_node(NULL, NONE, COST_UNDEF, rover_loc, 0, -1); // creation of an temporary node to initialized stat_game
    phase_tree->stat_game = init_stat_game(move_histo, 0, false_node_temp); // initialisation of stat_game

    phase_tree->stat_game = create_node_phase(nb_move_disp_phase, phase_tree->root, 1, map, rover_loc, move_histo, 0, phase_tree->stat_game, reg); // creation of the tree

    for(int k = phase_tree->stat_game->min_node_tree->depth; k < 6; k++){ // removal of movement in too much (with an index > node depth)
        phase_tree->stat_game->move_histo[k] = NONE;
    }

    return phase_tree;
}

/**
 * @brief the game function
 * @param *map_name : the name of the map that we want to play on
 */
void game(char *map_name){
    // display map made by Flasque //
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

    // definition of the localisation rover (random //
    srand(time(NULL));
    t_localisation rover_loc = loc_init(rand()%map.x_max, rand()%map.y_max, rand()%4);
    while(map.costs[rover_loc.pos.x][rover_loc.pos.y] == 0 && map.costs[rover_loc.pos.x][rover_loc.pos.y] != COST_UNDEF && map.costs[rover_loc.pos.x][rover_loc.pos.y] < 10000){
        rover_loc = loc_init(rand()%map.x_max, rand()%map.y_max, rand()%4);
    }

    // print information about the game (loc rover and loc base)//
    static char orientation[4][6] = {"NORTH", "EAST", "SOUTH", "WEST"};
    printf("\nRover start at : (x = %d  y = %d), %s", rover_loc.pos.x, rover_loc.pos.y, orientation[rover_loc.ori]);
    printf("\nThe Base is at : (x = %d  y = %d)\n", getBaseStationPosition(map).y, getBaseStationPosition(map).x);

    // game //
    t_stat_game *stat_game;
    int reach_base = 0;
    int count = 0;
    t_move **move_game = (t_move **)malloc(255 * sizeof(t_move *)); // list of list of t_move
    if(move_game == NULL){printf("Allocation error of the variable move_game in the game function");return;}

    while(reach_base != 1){ // while we not reach the base the game not end
        if(map.costs[rover_loc.pos.x][rover_loc.pos.y] >= 10000 && map.costs[rover_loc.pos.x][rover_loc.pos.y] != COST_UNDEF){ // if we start on a reg
            stat_game = phase_tree(getRandomMoves(9), map, rover_loc, 1)->stat_game;
            //printf("\nReg phase. (-1 move)"); // print if reg (for debug)
        }
        else{ // else
            stat_game = phase_tree(getRandomMoves(9), map, rover_loc, 0)->stat_game;
        }

        // actualisation of the game variables //
        reach_base = stat_game->reach_base; // if on base
        rover_loc = stat_game->min_node_tree->loc; // new rover localisation
        //print_stat_game(stat_game); // print of the stat_game for each phase (for debug)
        move_game[count] = stat_game->move_histo; // we put the move_histo that lead to the current location in the list move_game
        count++;
    }
    printf("\n\nLe Rover a atteint la Base !");
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