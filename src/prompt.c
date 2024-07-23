#include "prompt.h"
#include "makenx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void command_help(void) {
    printf("help                      Prints this message\n"
           "exit                      Exits the prompt\n"
           "evaluate                  Prints the result of the expression\n"
           "tree                      Prints the expression in tree format\n"
           "variables                 Prints the variables\n"
           "set <var-name> <value>    Assigns <value> to var <var-name>\n");
}

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

    char input_line[384];
    char command1[128];
    char command2[128];
    char command3[128];
    while (1) {
        printf("makenx%c ", '%');
        fgets(input_line, sizeof(input_line), stdin);
        sscanf(input_line, "%s %s %s", command1, command2, command3);
        if (strncmp(command1, "exit", 4) == 0) {
            destroy_node(root);
            destroy_token_stack(t_stack);
            destroy_var_stack(v_stack);
            exit(EXIT_SUCCESS);
        } else if (strncmp(command1, "help", 4) == 0) {
            command_help();
        } else if (strncmp(command1, "evaluate", 8) == 0) {
            if (!are_all_var_set(v_stack)) {
                printf("You must set values to all variables in order to "
                       "evaluate\n");
                continue;
            }
            printf("Result: %f\n", evaluate(root, v_stack));
        } else if (strncmp(command1, "tree", 4) == 0) {
            print_node(root, 0);
        } else if (strncmp(command1, "variables", 9) == 0) {
            print_var_stack(v_stack);
        } else if (strncmp(command1, "set", 3) == 0) {
            int index = does_var_exist(v_stack, command2);
            if (index == -1) {
                printf("Var %s does not exist\n", command2);
                continue;
            }
            double value = (double)atof(command3);
            set_var_value(v_stack, command2, value);
            printf("Var %s set to %f\n", command2, value);
        } else {
            printf(
                "Invalid command. Use 'help' to display available commands\n");
        }
    }
}
