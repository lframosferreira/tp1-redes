#include "common.h"

int main(int argc, char **argv) {

  if (argc != 5) {
    usage(stderr, argv[0]);
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
      usage(stderr, argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  char *ip_protocol = argv[1];
  int port = atoi(argv[2]);

  
  return 0;
}
