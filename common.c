#include "common.h"

// game related stuff

void print_board(const int board[BOARD_SIZE][BOARD_SIZE]) {
  char repr;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      switch (board[i][j]) {
      case BOMB:
        repr = '*';
        break;
      case HIDDEN:
        repr = '-';
        break;
      case 0:
        repr = '0';
        break;
      case FLAGGED:
        repr = '>';
        break;
      default:
        repr = board[i][j] + '0';
        break;
      }
      if (j == BOARD_SIZE - 1) {
        fprintf(stdout, "%c", repr);
      } else {
        fprintf(stdout, "%c\t\t", repr);
      }
    }
    fprintf(stdout, "\n");
  }
}

void reset_board_state(int board[BOARD_SIZE][BOARD_SIZE]) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = HIDDEN;
    }
  }
}

void parse_input(const char *input_file_path, int board[BOARD_SIZE][BOARD_SIZE]) {
  FILE *fp = fopen(input_file_path, "r");
  if (fp == NULL) {
   err_n_die("Error while opening the input file\n");
  }

  char line_buffer[MAX_BUFFER_SIZE];

  int i = 0;
  char *token;
  while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL){
    board[i][0] = atoi(strtok(line_buffer, ","));
    board[i][1] = atoi(strtok(NULL, ","));
    board[i][2] = atoi(strtok(NULL, ","));
    board[i][3] = atoi(strtok(NULL, ","));
    i++;
  }

  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      fprintf(stdout, "%d \n", board[i][j]);
    }
  }
  
  fclose(fp);
}

void server_usage(FILE *fp, const char *path) {
  const char *basename = strrchr(path, '/');
  basename = basename ? basename + 1 : path;
  fprintf(fp, "usage: %s [IP_PROTOCOL] [PORT] [OPTION]\n", basename);
  fprintf(fp, "  -i\t\t"
              "Path to input file.\n");
}

void client_usage(FILE *fp, const char *path) {
  const char *basename = strrchr(path, '/');
  basename = basename ? basename + 1 : path;
  fprintf(fp, "usage: %s [SERVER_ADDR] [PORT]\n", basename);
}

void err_n_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

bool is_out_of_bounds(const int coordinates[2]) {
  return coordinates[0] < 0 || coordinates[0] > BOARD_SIZE - 1 ||
         coordinates[1] < 0 || coordinates[1] > BOARD_SIZE - 1;
}