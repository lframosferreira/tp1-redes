#include "common.h"

void print_board(const int board[BOARD_SIZE][BOARD_SIZE]) {
  char repr;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      switch (board[i][j]) {
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
        repr = board[i][j] + '0';
        break;
      }
      fprintf(stdout, "%c\t\t", repr);
    }
    fprintf(stdout, "\n");
  }
}

void parse_input(const char *file_path) {
  FILE *fp = fopen(file_path, "r");
  if (fp == NULL) {
    perror("Error while opening the input file\n");
    exit(EXIT_FAILURE);
  }
  int board[BOARD_SIZE][BOARD_SIZE];
  fseek(fp, 0, SEEK_END);
  long filesize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *content = (char *)malloc(filesize + 1);
  if (content == NULL) {
    fclose(fp);
    perror("Error while allocating memory for the file content buffer\n");
    exit(EXIT_FAILURE);
  }
  // checar possivel erro: nro de bytes lidos esta correto? (retorno de fread)
  if (fread(content, sizeof(char), filesize, fp) != filesize) {
    perror("Error while reading from input file\n");
    exit(EXIT_FAILURE);
  }
  printf("%s\n", content);
  fclose(fp);
}

void usage(FILE *fp, const char *path) {
  const char *basename = strrchr(path, '/');
  basename = basename ? basename + 1 : path;
  fprintf(fp, "usage: %s [IP_PROTOCOL] [PORT] [OPTION]\n", basename);
  fprintf(fp, "  -i\t\t"
              "Path to input file.\n");
}
