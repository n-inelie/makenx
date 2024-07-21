#include "makenx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double evaluate(Node *n) {
    if (!isnan(n->value)) {
        return n->value;
    }

    double *sub_nodes_value;
    double result;
    switch (n->sub_nodes_count) {
    case 1:
        sub_nodes_value = malloc(sizeof(double) * 1);
        sub_nodes_value[0] = evaluate(n->sub_nodes[0]);
        switch (n->sym) {
        case ROOT:
            return sub_nodes_value[0];
            break;
        default:
            fprintf(stderr,
                    "Error: (dev) Invalid matching of symbol and "
                    "sub_nodes_count (%d)\n",
                    1);
            exit(EXIT_FAILURE);
            break;
        }
        break;
    case 2:
        sub_nodes_value = malloc(sizeof(double) * 2);
        sub_nodes_value[0] = evaluate(n->sub_nodes[0]);
        sub_nodes_value[1] = evaluate(n->sub_nodes[1]);
        printf("%f, %f\n", sub_nodes_value[0], sub_nodes_value[1]);
        switch (n->sym) {
        case ADD:
            result =  sub_nodes_value[0] + sub_nodes_value[1];
            free(sub_nodes_value);
            return result;
            break;
        case SUBTRACT:
            result =  sub_nodes_value[0] - sub_nodes_value[1];
            free(sub_nodes_value);
            return result;
            break;
        case MULTIPLY:
            result =  sub_nodes_value[0] * sub_nodes_value[1];
            free(sub_nodes_value);
            return result;
            break;
        case DIVIDE:
            result =  sub_nodes_value[0] / sub_nodes_value[1];
            free(sub_nodes_value);
            return result;
            break;
        case POW:
            result =  pow(sub_nodes_value[0], sub_nodes_value[1]);
            free(sub_nodes_value);
            return result;
            break;
        default:
            fprintf(stderr,
                    "Error: (dev) Invalid matching of symbol and "
                    "sub_nodes_count (%d)\n",
                    2);
            exit(EXIT_FAILURE);
            break;
        }
    }
    return NAN;
}
