#include "common.h"

void print_board(const struct *action){
    char repr;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++){
            switch (action->board[i][j]){
                case -1:
                    repr = '*';
                    break;
                case -2:
                    repr = '-';
                    break;
                case 0:
                    repr = '0'
                    break;
                case -3:
                    repr = '>';
                    break;
                default:
                    repr = action->board[i][j];
                    break;
            }
            fprintf(stdout, "%c ", repr);
        }
        fprintf(stdout, '\n');
    }
}


