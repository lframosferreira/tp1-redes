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

  int port = atoi(argv[2]);

  // por agora, nao vamos nos preocupar com o aprse do arquivo de entrada. Hard
  // codar um board aqui
  int board[BOARD_SIZE][BOARD_SIZE] = {
      {1, 2, -1, 1}, {1, -1, 2, 1}, {1, 2, 1, 1}, {0, 1, -1, 1}};



  


  return 0;
}
