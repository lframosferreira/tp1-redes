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
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = ntohs(server_port);

  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    err_n_die("Error on using inet_pton.\n");
  }

  if (connect(sockfd, (struct sockaddr *)(&servaddr), sizeof(servaddr)) == -1) {
    err_n_die("Error on connecting to server.\n");
  }

  char buffer[BUFFER_SIZE];
  for (;;) {

    memset(buffer, 0, sizeof(buffer));
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      err_n_die("fgets.\n");
    }

    if (send(sockfd, buffer, sizeof(buffer), 0) == -1) {
      err_n_die("Error on sending message to server.\n");
    }
  }

  close(sockfd);

  return 0;
}