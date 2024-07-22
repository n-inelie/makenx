#include "makenx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void handleStringNode(Node *n, Symbol sym,
                                    size_t sub_nodes_count) {
    n->sub_nodes_count = sub_nodes_count;
    n->sub_nodes = malloc(sizeof(Node) * sub_nodes_count);
    n->sym = sym;
    n->value = NAN;
}

void parse(TokenStack *t_stack, size_t stack_index, Node *current_node) {
    size_t fill = 0;
    Token t;
    Symbol sym;
    size_t paren_pair_count = 0;
    Node *n = malloc(sizeof(Node) * current_node->sub_nodes_count);

    for (size_t i = stack_index; i < t_stack->size; ++i) {
        if (fill == current_node->sub_nodes_count) {
            break;
        }
        t = t_stack->tokens[i];
        switch (t.type) {
        case L_PAREN:
            paren_pair_count++;
            break;
        case R_PAREN:
            if (paren_pair_count != 0) {
                paren_pair_count--;
                continue;
            }
            if (i - stack_index != fill) {
                fprintf(stderr, "Error: Not enough args provided for %s\n",
                        t_stack->tokens[stack_index - 1].text);
                exit(EXIT_FAILURE);
            }
            break;
        case COMMA:
            break;
        case OPERATOR:
            fprintf(stderr, "Error: (dev) Could not filter the token stack\n");
            break;
        case STRING:
            sym = GetSymbol(t.text);
            switch (sym) {
            case ADD:
                handleStringNode(n + fill, ADD, 2);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                i++;
                break;
            case MULTIPLY:
                handleStringNode(n + fill, MULTIPLY, 2);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case SUBTRACT:
                handleStringNode(n + fill, SUBTRACT, 2);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case DIVIDE:
                handleStringNode(n + fill, DIVIDE, 2);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case POW:
                handleStringNode(n + fill, POW, 2);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case FACT:
                handleStringNode(n + fill, FACT, 1);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case LN:
                handleStringNode(n + fill, LN, 1);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case LOG10:
                handleStringNode(n + fill, LOG10, 1);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case LOG2:
                handleStringNode(n + fill, LOG2, 1);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case LOGAB:
                handleStringNode(n + fill, LOGAB, 2);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case SIN:
                handleStringNode(n + fill, SIN, 1);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case COS:
                handleStringNode(n + fill, COS, 1);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case TAN:
                handleStringNode(n + fill, TAN, 1);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
                break;
            case PERIOD:
                handleStringNode(n + fill, PERIOD, 2);
                parse(t_stack, ++i, n + fill);
                current_node->sub_nodes[fill] = n + fill;
                fill++;
            default:
                fprintf(stderr,
                        "Error: Invalid string %s\n"
                        "Variable support is yet to be added\n",
                        t.text);
                exit(EXIT_FAILURE);
                break;
            }
            break;
        case NUMERIC:
            n[fill].sub_nodes_count = 0;
            n[fill].sub_nodes = NULL;
            n[fill].sym = NUMBER;
            n[fill].value = (double)atoi(t.text);

            current_node->sub_nodes[fill] = n + fill;
            fill++;
            break;
        }
        if (i == t_stack->size - 1) {
            if (fill != current_node->sub_nodes_count) {
                fprintf(stderr, "Error: Not enough args provided for %s\n",
                        t_stack->tokens[stack_index - 1].text);
                exit(EXIT_FAILURE);
            }
        }
    }
}
