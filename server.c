#include "common.h"

int main(int argc, char **argv) {

  if (argc != 5) {
    server_usage(stderr, argv[0]);
    exit(EXIT_FAILURE);
  }

  int option;
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
  }

  // fazer strcmp e gerar inteiro correto AF_INET ou AF_INET6
  char *ip_protocol = argv[1];
  int domain;
  if (strcmp(ip_protocol, "v4")) {
    domain = AF_INET;
  } else if (strcmp(ip_protocol, "v6")) {
    domain = AF_INET6;
  } else {
    err_n_die("Protocol family not supported\n");
  }

  int port = atoi(argv[2]);

  // por agora, nao vamos nos preocupar com o aprse do arquivo de entrada. Hard
  // codar um board aqui
  int board[BOARD_SIZE][BOARD_SIZE] = {
      {1, 2, -1, 1}, {1, -1, 2, 1}, {1, 2, 1, 1}, {0, 1, -1, 1}};

  int sockfd = socket(domain, SOCK_STREAM, 0);
  if (sockfd == -1) {
    err_n_die("Error while opening server socket.\n");
  }

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = port;

  if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1){
    err_n_die("Erro in bind.\n");
  }

  if (listen(sockfd, 1) == -1){
    err_n_die("Erro on listen.\n");
  }

  int connfd;
  for(;;){
    struct sockaddr_in addr;
    socklen_t addr_len;

    connfd = accept(sockfd, (struct sockaddr *) NULL, NULL);

  }


  return 0;
}
