#include "makenx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse(TokenStack *t_stack, size_t stack_index, Node *current_node) {
    size_t fill = 0;
    Token t;
    Node *n = malloc(sizeof(Node));

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
                n->sub_nodes_count = 2;
                n->sub_nodes = malloc(sizeof(Node *) * n->sub_nodes_count);
                n->sym = ADD;
                n->value = NAN;

                stack_index++;
                parse(t_stack, stack_index, n);

                current_node->sub_nodes[fill] = n;
                fill++;
            }
            break;
        case NUMERIC:
            n->sub_nodes_count = 0;
            n->sub_nodes = NULL;
            n->sym = NUMBER;
            n->value = (double)atoi(t.text);

            stack_index++;
            parse(t_stack, stack_index, n);

            current_node->sub_nodes[fill] = n;
            fill++;
            break;
        }
    }
}
