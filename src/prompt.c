#include "prompt.h"
#include "makenx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_prompt(char *str) {
    TokenStack *t_stack = create_token_stack(16);
    VarStack *v_stack = create_var_stack(4);

    Node *root = malloc(sizeof(*root));
    root->sym = ROOT;
    root->sub_nodes_count = 1;
    root->sub_nodes = malloc(sizeof(Node *));
    root->value = NAN;

    tokenize(t_stack, str);
    filter_token_stack(t_stack);
    parse(t_stack, 0, v_stack, root);

    char command[256];
    while (1) {
        printf("makenx%c ", '%');
        scanf("%s", command);
        if (strncmp(command, "exit", 4) == 0) {
            destroy_node(root);
            destroy_token_stack(t_stack);
            destroy_var_stack(v_stack);
            exit(EXIT_SUCCESS);
        } else if (strncmp(command, "help", 4) == 0) {
            printf("help        Prints this message\n"
                   "exit        Exits the prompt\n"
                   "evaluate    Prints the result of the expression\n"
                   "tree        Prints the expression in tree format\n"
                   "variables   Prints the variables\n");
        } else if (strncmp(command, "evaluate", 8) == 0) {
            printf("Result: %f\n", evaluate(root));
        } else if (strncmp(command, "tree", 4) == 0) {
            print_node(root, 0);
        } else if (strncmp(command, "variables", 9) == 0) {
            print_var_stack(v_stack);
        } else {
            printf(
                "Invalid command. Use 'help' to display available commands\n");
        }
    }
}
