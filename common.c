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
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL){
        perror("Erro ao abrir arquivo de tabuleiro inicial\n");
        exit(EXIT_FAILURE);
    }
    int board[BOARD_SIZE][BOARD_SIZE];
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *content = (char *)malloc(filesize + 1);
    if (content == NULL){
        fclose(fp);
        perror("Erro ao alocar memória para consumir conte[udo do arquivo\n");
        exit(EXIT_FAILURE);
    }
    // checar possivel erro: nro de bytes lidos esta correto? (retorno de fread)
    fread(content, sizeof(char), filesize, fp);
    printf("%s\n", content);
    fclose(fp);
}
