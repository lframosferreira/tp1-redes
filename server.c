#include "common.h"

int main(int argc, char **argv) {

  if (argc != 5) {
    server_usage(stderr, argv[0]);
    exit(EXIT_FAILURE);
  }

  char *addr_family = argv[1];
  char *portstr = argv[2];

  struct sockaddr_storage servaddr;
  memset(&servaddr, 0, sizeof(servaddr));

  if (server_sockaddr_init(addr_family, portstr, &servaddr) == -1) {
    err_n_die("Error while using server_sockaddr_init().\n");
  }

  char *input_file_path;
  int option;
  while ((option = getopt(argc, argv, "i:")) != -1) {
    switch (option) {
    case 'i':
      input_file_path = optarg;
      break;
    case '?':
      server_usage(stderr, argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  int game_board[BOARD_SIZE][BOARD_SIZE];
  parse_input(input_file_path, game_board);
  print_board(game_board);

  int sockfd = socket(servaddr.ss_family, SOCK_STREAM, 0);
  if (sockfd == -1) {
    err_n_die("Error while opening server socket.\n");
  }

  if (bind(sockfd, (struct sockaddr *)(&servaddr), sizeof(servaddr)) == -1) {
    close(sockfd);
    err_n_die("Error in bind().\n");
  }

  if (listen(sockfd, MAX_CLIENTS) == -1) {
    close(sockfd);
    err_n_die("Error on listen().\n");
  }

  for (;;) {

    struct sockaddr_storage client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int csockfd =
        accept(sockfd, (struct sockaddr *)(&client_addr), &client_addr_len);
    if (csockfd == -1) {
      err_n_die("Error on using accept().\n");
    }

    fprintf(stdout, "cilent connected\n");

    struct action curr_action;
    memset(&curr_action, 0, sizeof(curr_action));

    /* Pela especificação, sempre será utilizado um tabuleiro com 16 células e
     * exatamente 3 células são bombas. Logo, para que um jogo termine, o número
     * de células reveladas que não são bombas deve ser 13. A checagem de
     * vitória do jogo é feita dessa maneira para evitar overheads que, embora
     * não sejam de grande impacto para instâncias tão pequenas, podem ser um
     * problema com o aumento do tabuleiro do jogo */
    int revealed_cell_count = 0;
    const int NOT_BOMB_CELL_COUNT = 13;

    for (;;) {
      ssize_t bytes_received =
          recv(csockfd, &curr_action, sizeof(curr_action), 0);
      if (bytes_received == -1) {
        close(sockfd);
        close(csockfd);
        err_n_die("Error when using recv().\n");
      } else if (bytes_received == 0) { // client disconnected
        close(csockfd);
        break;
      }

      int c0 = curr_action.coordinates[0];
      int c1 = curr_action.coordinates[1];

      switch (curr_action.type) {
      case START:
        reset_board_state(curr_action.board);
        break;
      case REVEAL:
        if (game_board[c0][c1] == BOMB) {
          curr_action.type = GAME_OVER;
          for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
              curr_action.board[i][j] = game_board[i][j];
            }
          }
        } else {
          revealed_cell_count++;
          if (revealed_cell_count == NOT_BOMB_CELL_COUNT) {
            curr_action.type = WIN;
            for (int i = 0; i < BOARD_SIZE; i++) {
              for (int j = 0; j < BOARD_SIZE; j++) {
                curr_action.board[i][j] = game_board[i][j];
              }
            }
          } else {
            curr_action.type = STATE;
            curr_action.board[c0][c1] = game_board[c0][c1];
          }
        }
        break;
      case FLAG:
        curr_action.type = STATE;
        curr_action.board[c0][c1] = FLAGGED;
        break;
      case REMOVE_FLAG:
        curr_action.type = STATE;
        curr_action.board[c0][c1] = HIDDEN;
        break;
      case RESET:
        revealed_cell_count = 0;
        curr_action.type = STATE;
        reset_board_state(curr_action.board);
        fprintf(stdout, "starting new game\n");
        break;
      case EXIT:
        fprintf(stdout, "client disconnected\n");
        reset_board_state(curr_action.board);
        break;
      default:
        break;
      }

      if (send(csockfd, &curr_action, sizeof(curr_action), 0) == -1) {
        close(sockfd);
        close(csockfd);
        err_n_die("Error using send().\n");
      }
    }
  }

  close(sockfd);
  return 0;
}
