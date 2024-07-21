#include "makenx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "Error: No input string/file provided\n"
                        "Type 'help' to list out available commands\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stderr, "Too many arguments provided\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s", argv[1]);

    if (strncmp(buffer, "help", 4) == 0) {
        printf("help        Prints this message\n"
               "<string>    Evaluates the given string\n"
               "<file_path> Evaluates the expression given in the file\n");
    }

    TokenStack *t_stack = CreateStack(16);
    Stats stats = {0, 0, 0, 0};

    tokenize(&stats, t_stack, buffer);

    if (stats.l_paren_count != stats.r_paren_count) {
        fprintf(stderr, "Error: Failed to parse, missing parenthesis\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < t_stack->size; ++i) {
        printf("%s\n", t_stack->tokens[i].text);
    }

    destroyTokenStack(t_stack);

    return 0;
}
