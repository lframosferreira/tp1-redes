#include "common.h"

int main(int argc, char **argv) {

  if (argc != 4) {
    server_usage(stderr, argv[0]);
    exit(EXIT_FAILURE);
  }

  /* int option;
  char *input_file_path;
  while ((option = getopt(argc, argv, "i:")) != -1) {
    switch (option) {
    case 'i':
      input_file_path = optarg;
      break;
    case '?':
      server_usage(stderr, argv[0]);
      exit(EXIT_FAILURE);
    }
  } */

  char *input_file_path = argv[3];

  // fazer strcmp e gerar inteiro correto AF_INET ou AF_INET6
  char *ip_protocol = argv[1];
  int domain;
  if (strcmp(ip_protocol, "v4")) {
    domain = AF_INET;
  } else if (strcmp(ip_protocol, "v6")) {
    domain = AF_INET6;
  } else {
    err_n_die("Protocol family not supserver_ported\n");
  }

  int server_port = atoi(argv[2]);

  // por agora, nao vamos nos preocupar com o aprse do arquivo de entrada. Hard
  // codar um board aqui
  int board[BOARD_SIZE][BOARD_SIZE] = {
      {1, 2, -1, 1}, {1, -1, 2, 1}, {1, 2, 1, 1}, {0, 1, -1, 1}};

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    err_n_die("Error while opening server socket.\n");
  }

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(server_port);

  if (bind(sockfd, (struct sockaddr *)(&servaddr), sizeof(servaddr)) == -1) {
    err_n_die("Error in bind.\n");
  }

  if (listen(sockfd, 10) == -1) {
    err_n_die("Error on listen.\n");
  }

  int csockfd;
  char msg[10];
  for (;;) {
    struct sockaddr_in client_addr;

    csockfd =
        accept(sockfd, (struct sockaddr *)(&client_addr), sizeof(client_addr));

    if (csockfd == -1) {
      err_n_die("Não sei se deveria estar aqui, mas erro ao fzr accept\n.");
    }
    if (recvfrom(csockfd, msg, sizeof(msg), 0,
                 (struct sockaddr *)(&client_addr),
                 sizeof(client_addr)) == -1) {
      err_n_die("n sei se devia ser aq tb, mas recvfrom\n");
    };
    printf("o gigantesco %s\n", msg);

    close(csockfd);
  }

  close(sockfd);

  return 0;
}
