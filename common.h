#ifndef COMMON_H
#define COMMON_H

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Action types
#define START 0
#define REVEAL 1
#define FLAG 2
#define STATE 3
#define REMOVE_FLAG 4
#define RESET 5
#define WIN 6
#define EXIT 7
#define GAME_OVER 8

// Cell types
#define BOMB -1
#define HIDDEN -2
#define FLAGGED -3

#define BOARD_SIZE 4
#define MAX_BUFFER_SIZE 1024
#define MAX_CLIENTS 10

struct action {
  int type;
  int coordinates[2];
  int board[BOARD_SIZE][BOARD_SIZE];
};

void print_board(const int board[BOARD_SIZE][BOARD_SIZE]);
void reset_board_state(int board[BOARD_SIZE][BOARD_SIZE]);
void parse_input(const char *input_file_path,
                 int board[BOARD_SIZE][BOARD_SIZE]);
void server_usage(FILE *fp, const char *path);
void client_usage(FILE *fp, const char *path);
void err_n_die(const char *msg);
bool is_out_of_bounds(const int coordinates[2]);

// Funções baseada na implementação disponibilizada na playlist do professor
// Ítalo Cunha https://www.youtube.com/watch?v=tJ3qNtv0HVs&t=2s
int addrparse(const char *addrstr, const char *portstr,
              struct sockaddr_storage *storage);
int server_sockaddr_init(const char *addr_family, const char *porstr,
                         struct sockaddr_storage *storage);
#endif