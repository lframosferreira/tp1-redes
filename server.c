#include "common.h"

int main(int argc, char **argv){

    int option;
    char *input_file_path;
    while ((option = getopt(argc, argv, "i:")) != -1){
        switch (option){
            case 'i':
                input_file_path = "oi";
        }
    }
    return 0;
}

