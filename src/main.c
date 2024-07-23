#include "prompt.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "Error: No input string provided\n"
                        "Type 'help' to list out available commands\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stderr, "Error: Too many arguments provided\n"
                        "Use 'help' to print available commands\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s", argv[1]);

    if (strncmp(buffer, "help", 4) == 0) {
        printf("help               Prints this message\n"
               "<string>           Starts prompt to perform actions on the "
               "expression\n");
        return 1;
    }

    start_prompt(buffer);

    return 0;
}
