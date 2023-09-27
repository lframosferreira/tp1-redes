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

  int curr_board_state[BOARD_SIZE][BOARD_SIZE] = {
      {-2, -2, -2, -2}, {-2, -2, -2, -2}, {-2, -2, -2, -2}, {-2, -2, -2, -2}};

  char command_buffer[MAX_BUFFER_SIZE];
  for (;;) {

    memset(command_buffer, 0, sizeof(command_buffer));
    if (fgets(command_buffer, sizeof(command_buffer), stdin) == NULL) {
      err_n_die("fgets.\n");
    }
    size_t new_line_pos = strlen(command_buffer) - 1;
    command_buffer[new_line_pos] = '\0';
    struct action curr_action;

    if (strcmp(command_buffer, "start") == 0) {
      curr_action.type = START;
      print_board(curr_board_state);
    } else if (strcmp(command_buffer, "reset") == 0) {
      curr_action.type = RESET;
      fprintf(stdout, "starting new game\n");
      reset_board(curr_board_state);
      print_board(curr_board_state);
    } else if (strcmp(command_buffer, "exit") == 0) {
      curr_action.type = EXIT;
      close(sockfd); // é isso msm?
      exit(EXIT_SUCCESS);
    } else {
      char *token = strtok(command_buffer, " ");
      char *coordinates = strtok(NULL, " ");

      // vamos assumir inicialmente que as coordenadas sempre vem corretamente
      char *c0 = strtok(coordinates, ",");
      char *c1 = strtok(NULL, ",");
      curr_action.coordinates[0] = atoi(c0);
      curr_action.coordinates[1] = atoi(c1);
      if (strcmp(token, "reveal") == 0) {
        curr_action.type = REVEAL;
        print_board(curr_board_state);
      } else if (strcmp(token, "flag") == 0) {
        curr_action.type = FLAG;
        print_board(curr_board_state);
      } else if (strcmp(command_buffer, "remove_flag") == 0) {
        curr_action.type = REMOVE_FLAG;
        print_board(curr_board_state);
      } else {
        fprintf(stderr, "error: command not found\n");
      }
    }

    if (send(sockfd, command_buffer, sizeof(command_buffer), 0) == -1) {
      err_n_die("Error on sending message to server.\n");
    }
  }

  close(sockfd);

  return 0;
}