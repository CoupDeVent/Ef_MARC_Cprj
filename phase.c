//
// Created by eytan on 11/11/2024.
//

#include "phase.h"
#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

int *nb_move_disp_phase(int *nb_move_disp){
    int nb_move_disp_phase[7];

    for(int k = 0; k < 8; k++){
        int alt = rand()%7;

        if(nb_move_disp[alt] > 0){
            nb_move_disp_phase[alt]++;
            nb_move_disp[alt]--; // a test
        }
        else{k--;}
    }
    return nb_move_disp_phase;
}

int phase_tree(int nb_move_disp_phase){


    int temp_score = 0; // temp score
    int temp_orientation; // temp orientation


    t_tree *phase_tree = (t_tree *)malloc(sizeof(t_tree));

    for(int i = 0; i < 7; i++){
        do{
            phase_tree->root = create_node(NULL, i, temp_score, temp_orientation);
        }while(nb_move_disp_phase[i] > 0);
    }
}


/*
 * local fonc
 */

