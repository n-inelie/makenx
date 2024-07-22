#include "makenx.h"
#include <stdio.h>

void print_node(Node *n, size_t padding) {
    for (size_t i = 0; i < padding; ++i) {
        printf(" ");
    }
    switch (n->sym) {
    case ROOT:
        printf("root ");
        break;
    case ADD:
        printf("add ");
        break;
    case MULTIPLY:
        printf("mul ");
        break;
    case SUBTRACT:
        printf("sub ");
        break;
    case DIVIDE:
        printf("div ");
        break;
    case LN:
        printf("ln ");
        break;
    case LOG10:
        printf("log10 ");
        break;
    case LOG2:
        printf("log2 ");
        break;
    case LOGAB:
        printf("logab ");
        break;
    case FACT:
        printf("fact ");
        break;
    case NUMBER:
        printf("number ");
        break;
    case PERIOD:
        printf("period ");
        break;
    case SIN:
        printf("sin ");
        break;
     case COS:
        printf("cos ");
        break;
     case TAN:
        printf("tan ");
        break;
  default:
        break;
    }
    printf("%f\n", n->value);
    padding += 2;
    for (size_t i = 0; i < n->sub_nodes_count; ++i) {
        print_node(n->sub_nodes[i], padding);
    }
}
