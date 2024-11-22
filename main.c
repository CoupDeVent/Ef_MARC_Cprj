#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "binary_tree.h"
#include "phase.h"

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
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

    /*
    int *nb_move_test = (int *)malloc(7 * sizeof(int));
    nb_move_test[0] = 1;nb_move_test[1] = 2;nb_move_test[2] = 0;nb_move_test[3] = 1;nb_move_test[4] = 2;nb_move_test[5] = 3;nb_move_test[6] = 0;
     */
    t_localisation rover_loc = loc_init(5,5,NORTH);
    printf("\n\nTree : \n");
    t_tree *phase_tree_test = phase_tree(getRandomMoves(9), map, rover_loc);
    print_tree(phase_tree_test->root, 0);


    return 0;
}
