#ifndef COMMON_H
#define COMMON_H

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
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

#define BOARD_SIZE 4

struct action {
  int type;
  int coordinates[2];
  int board[BOARD_SIZE][BOARD_SIZE];
};

// game related stuff

void print_board(const struct action *current_action);
void parse_input(const char *filepath);

// general

void usage(FILE *fp, const char *path);

#endif