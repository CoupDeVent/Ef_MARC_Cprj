//
// Created by eytan on 11/11/2024.
//

#include "phase.h"
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // pour rand

int *nb_move_disp_phase(){
    int nb_move_disp_phase[7];
    int nb_move_disp[7] = {22, 15, 7, 7, 21, 21, 7};

    srand(time(NULL)); // pour rand

    for(int k = 0; k < 8; k++){
        int random = (rand()%7) + 1; // rand random = (rand() % (MAX + 1 - MIN)) + MIN;

        if(nb_move_disp[random] > 0){
            nb_move_disp_phase[random]++;
            nb_move_disp[random]--; // a test
        }
        else{k--;}
    }
    return nb_move_disp_phase;
}

/*
 * t_move *getRandomMoves(int N)
{
    int nbmoves[]={22,15,7,7,21,21,7};
    int total_moves=100;
    t_move *moves = (t_move *)malloc(N * sizeof(t_move));
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
 */


int phase_tree(int nb_move_disp_phase){


    int temp_score = 0; // temp score
    int temp_orientation; // temp orientation


    t_tree *phase_tree = (t_tree *)malloc(sizeof(t_tree));

    for(int i = 0; i < 7; i++){
        do{
            phase_tree->root = create_node(NULL, i, temp_score, temp_orientation); // mais faire par queue pour retrouver le chemin
        }while(nb_move_disp_phase[i] > 0);
    }
}


/*
 * local fonc
 */

