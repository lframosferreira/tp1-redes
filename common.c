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

int addrparse(const char *addrstr, const char *portstr,
              struct sockaddr_storage *storage) {
  if (addrstr == NULL || portstr == NULL) {
    return -1;
  }
  uint16_t port = (uint16_t)atoi(portstr);
  if (port == 0) {
    return -1;
  }
  port = htons(port);

  memset(storage, 0, sizeof(*storage));

  struct in_addr inaddr4;
  if (inet_pton(AF_INET, addrstr, &inaddr4) == 1) {
    struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
    addr4->sin_family = AF_INET;
    addr4->sin_port = port;
    addr4->sin_addr = inaddr4;
    return 0;
  }

  struct in6_addr inaddr6;
  if (inet_pton(AF_INET6, addrstr, &inaddr6) == 1) {
    struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
    addr6->sin6_family = AF_INET6;
    addr6->sin6_port = port;
    memcpy(&(addr6->sin6_addr), &inaddr6, sizeof(inaddr6));
    return 0;
  }

  return -1;
}

int server_sockaddr_init(const char *addr_family, const char *portstr,
                         struct sockaddr_storage *storage) {
  if (addr_family == NULL || portstr == NULL) {
    return -1;
  }
  uint16_t port = (uint16_t)atoi(portstr);
  if (port == 0) {
    return -1;
  }
  port = htons(port);

  memset(storage, 0, sizeof(*storage));

  if (strcmp(addr_family, "v4") == 0) {
    struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
    addr4->sin_family = AF_INET;
    addr4->sin_port = port;
    addr4->sin_addr.s_addr = INADDR_ANY;
    return 0;
  }

  if (strcmp(addr_family, "v6") == 0) {
    struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
    addr6->sin6_family = AF_INET6;
    addr6->sin6_port = port;
    addr6->sin6_addr = in6addr_any;
    return 0;
  }

  return -1;
}