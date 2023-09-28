#include "common.h"

int main(int argc, char **argv) {

  if (argc != 3) {
    client_usage(stderr, argv[0]);
    exit(EXIT_FAILURE);
  }

  // void addr = parse_addr(argv[1]);
  int server_port = atoi(argv[2]);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    err_n_die("Erro while opening client socket\n.");
  }

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = ntohs(server_port);

  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    err_n_die("Error on using inet_pton.\n");
  }

  if (connect(sockfd, (struct sockaddr *)(&servaddr), sizeof(servaddr)) == -1) {
    err_n_die("Error on connecting to server.\n");
  }

  char input_buffer[MAX_BUFFER_SIZE];
  char *command;
  char *coordinates;
  ssize_t bytes_received;

  struct action curr_action;
  memset(&curr_action, 0, sizeof(curr_action));

  for (;;) {

    memset(input_buffer, 0, sizeof(input_buffer));
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
      err_n_die("fgets.\n");
    }

    command = strtok(input_buffer, " ");
    command[strcspn(command, "\n")] = '\0';

    coordinates = strtok(NULL, " ");
    if (coordinates != NULL) {
      char *first_coordinate = strtok(coordinates, ",");
      char *second_coordinate = strtok(NULL, ",");
      curr_action.coordinates[0] = atoi(first_coordinate);
      curr_action.coordinates[1] = atoi(second_coordinate);
    }

    int c0 = curr_action.coordinates[0];
    int c1 = curr_action.coordinates[1];

    if (strcmp(command, "start") == 0) {
      curr_action.type = START;
    } else if (strcmp(command, "reset") == 0) {
      curr_action.type = RESET;
      fprintf(stdout, "starting new game\n");
    } else if (strcmp(command, "exit") == 0) {
      curr_action.type = EXIT;
    } else if (strcmp(command, "reveal") == 0) {
      curr_action.type = REVEAL;
      if (is_out_of_bounds(curr_action.coordinates)) {
        fprintf(stdout, "error: invalid cell\n");
        continue;
      }
      if (curr_action.board[c0][c1] != HIDDEN &&
          curr_action.board[c0][c1] != FLAGGED) {
        fprintf(stdout, "error: cell already revealed\n");
        continue;
      }
    } else if (strcmp(command, "flag") == 0) {
      curr_action.type = FLAG;
      if (curr_action.board[c0][c1] != HIDDEN) {
        fprintf(stdout, "error: cannot insert flag in revealed cell\n");
        continue;
      }
      if (curr_action.board[c0][c1] == FLAGGED) {
        fprintf(stdout, "error: cell already has flag\n");
        continue;
      }
    } else if (strcmp(command, "remove_flag") == 0) {
      curr_action.type = REMOVE_FLAG;
    } else {
      fprintf(stdout, "error: command not found\n");
      continue; // dont send anything to server
    }

    if (send(sockfd, &curr_action, sizeof(curr_action), 0) == -1) {
      err_n_die("Error on using send().\n");
    }

    memset(&curr_action, 0, sizeof(curr_action));

    bytes_received = recv(sockfd, &curr_action, sizeof(curr_action), 0);
    if (bytes_received == -1) {
      err_n_die("Error when using recv().\n");
    } else if (bytes_received == 0) {
      break;
    }

    switch (curr_action.type) {
    case WIN:
      fprintf(stdout, "VASCO\n");
      break;
    case GAME_OVER:
      fprintf(stdout, "GOL DOS CARA\n");
      break;
    default:
      break;
    }
    print_board(curr_action.board);
  }

  close(sockfd);

  return 0;
}