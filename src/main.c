#include "makenx.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

Symbol OMap[1024];

int main(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "Error: No input string/file provided\n"
                        "Type 'help' to list out available commands\n");
        return 1;
    }

    if (argc > 3) {
        fprintf(stderr, "Error: Too many arguments provided\n"
                        "Use 'help' to print available commands\n");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s", argv[1]);

    if (strncmp(buffer, "help", 4) == 0) {
        printf("help               Prints this message\n"
               "<string>           Evaluates the given string\n"
               "<string> --tree    Evaluates the given string and prints the "
               "tree\n");
        return 1;
    }

    bool print_node = false;
    if (argc == 3 && strncmp(argv[2], "--tree", 6) == 0) {
        print_node = true;
    } else if (argc != 2) {
        fprintf(stderr, "Error: Invalid arguments provided\n"
                        "Use 'help' to print "
                        "available commands\n");
        exit(EXIT_FAILURE);
    }

    TokenStack *t_stack = CreateStack(16);
    Stats stats = {0, 0, 0, 0};

    tokenize(&stats, t_stack, buffer);

    if (stats.l_paren_count != stats.r_paren_count) {
        fprintf(stderr, "Error: Failed to parse, missing parenthesis\n");
        exit(EXIT_FAILURE);
    }

    filterTokenStack(t_stack);

    Node *root = malloc(sizeof(Node));
    root->sym = ROOT;
    root->sub_nodes_count = 1;
    root->sub_nodes = malloc(sizeof(Node *));
    root->value = NAN;

    initOMap();
    parse(t_stack, 0, root);

    printf("%f\n", evaluate(root));

    if (print_node) {
        printNode(root, 0);
    }

    destroyNode(root);
    destroyTokenStack(t_stack);

    return 0;
}
