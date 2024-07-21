#include "makenx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse(TokenStack *t_stack, size_t stack_index, Node *current_node) {
    size_t fill = 0;
    Token t;
    Node *n = malloc(sizeof(Node) * current_node->sub_nodes_count);

    for (size_t i = stack_index; i < t_stack->size; ++i) {
        if (fill == current_node->sub_nodes_count) {
            break;
        }
        t = t_stack->tokens[stack_index];
        switch (t.type) {
        case L_PAREN:
            break;
        case R_PAREN:
            break;
        case COMMA:
            break;
        case PERIOD:
            break;
        case OPERATOR:
            break;
        case STRING:
            if (strncmp(t.text, "add", 3) == 0) {
                n[fill].sub_nodes_count = 2;
                n[fill].sub_nodes = malloc(sizeof(Node *) * n[fill].sub_nodes_count);
                n[fill].sym = ADD;
                n[fill].value = NAN;

                stack_index++;
                parse(t_stack, stack_index, n + fill);

                current_node->sub_nodes[fill] = n;
                fill++;
            } else if (strncmp(t.text, "mul", 3) == 0) {
                n[fill].sub_nodes_count = 2;
                n[fill].sub_nodes = malloc(sizeof(Node *) * n[fill].sub_nodes_count);
                n[fill].sym = MULTIPLY;
                n[fill].value = NAN;

                stack_index++;
                parse(t_stack, stack_index, n + fill);

                current_node->sub_nodes[fill] = n;
                fill++;
            }
            break;
        case NUMERIC:
            n[fill].sub_nodes_count = 0;
            n[fill].sub_nodes = NULL;
            n[fill].sym = NUMBER;
            n[fill].value = (double)atoi(t.text);

            stack_index++;

            current_node->sub_nodes[fill] = n + fill;
            fill++;
            break;
        }
    }
}
