#include "common.h"

void print_board(const struct action *current_action){
    char repr;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++){
            switch (current_action->board[i][j]){
                case -1:
                    repr = '*';
                    break;
                case -2:
                    repr = '-';
                    break;
                case 0:
                    repr = '0';
                    break;
                case -3:
                    repr = '>';
                    break;
                default:
                    repr = current_action->board[i][j];
                    break;
            }
            fprintf(stdout, "%c ", repr);
        }
        fprintf(stdout, "\n");
    }
}

void parse_input(const char *filepath){
    FILE *file = fopen(filepath, "r");
    if (file == NULL){
        fprintf(stderr, "Erro ao abrir arquivo de tabuleiro inicial\n");
        exit(EXIT_FAILURE);
    }

    int board[BOARD_SIZE][BOARD_SIZE];
}
