#include "common.h"

int main(int argc, char **argv) {

  if (argc != 3) {
    client_usage(stderr, argv[0]);
    exit(EXIT_FAILURE);
  }

  //void addr = parse_addr(argv[1]);
  int port = argv[2];

  return 0;
}