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

void parse_input(const char *input_file_path,
                 int board[BOARD_SIZE][BOARD_SIZE]) {
  FILE *fp = fopen(input_file_path, "r");
  if (fp == NULL) {
    err_n_die("Error while opening the input file\n");
  }

  char line_buffer[MAX_BUFFER_SIZE];

  int i = 0;
  while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL) {
    board[i][0] = atoi(strtok(line_buffer, ","));
    board[i][1] = atoi(strtok(NULL, ","));
    board[i][2] = atoi(strtok(NULL, ","));
    board[i][3] = atoi(strtok(NULL, ","));
    i++;
  }

  fclose(fp);
}

// Função baseada na implementação disponibilizada na playlist do professor
// Ítalo Cunha https://www.youtube.com/watch?v=tJ3qNtv0HVs&t=2s
int addrparser(const char *addr_family, const char *portstr,
               struct sockaddr_storage *storage) {
  if (portstr == NULL) {
    return -1;
  }
  uint16_t port = (uint16_t)atoi(portstr);
  if (port == 0) {
    return -1;
  }
  port = htons(port);

  if (strcmp(addr_family, "v4") == 0) {
    struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
    addr4->sin_family = AF_INET;
    addr4->sin_port = port;
    return 0;
  }

  if (strcmp(addr_family, "v6") == 0) {
    struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
    addr6->sin6_family = AF_INET6;
    addr6->sin6_port = port;
    return 0;
  }

  return -1;
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