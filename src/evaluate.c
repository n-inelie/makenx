#include "makenx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double evaluate(Node *n) {
    if (!isnan(n->value)) {
        return n->value;
    }

    double *sub_nodes_value;
    double result = NAN;
    switch (n->sub_nodes_count) {
    case 1:
        sub_nodes_value = malloc(sizeof(double) * 1);
        sub_nodes_value[0] = evaluate(n->sub_nodes[0]);
        switch (n->sym) {
        case ROOT:
            result = sub_nodes_value[0];
            break;
        case SIN:
            result = sin(sub_nodes_value[0]);
            break;
        case COS:
            result = cos(sub_nodes_value[0]);
            break;
        case TAN:
            result = tan(sub_nodes_value[0]);
            break;
        case LN:
            result = log(sub_nodes_value[0]);
            break;
        case LOG10:
            printf("%f\n", sub_nodes_value[0]);
            result = log10(sub_nodes_value[0]);
            break;
        case LOG2:
            result = log2(sub_nodes_value[0]);
            break;
        case FACT:
            // TODO
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
        // printf("%f, %f\n", sub_nodes_value[0], sub_nodes_value[1]);
        switch (n->sym) {
        case ADD:
            result = sub_nodes_value[0] + sub_nodes_value[1];
            break;
        case SUBTRACT:
            result = sub_nodes_value[0] - sub_nodes_value[1];
            break;
        case MULTIPLY:
            result = sub_nodes_value[0] * sub_nodes_value[1];
            break;
        case DIVIDE:
            result = sub_nodes_value[0] / sub_nodes_value[1];
            break;
        case POW:
            result = pow(sub_nodes_value[0], sub_nodes_value[1]);
            break;
        case LOGAB:
            result = log(sub_nodes_value[0]) / log(sub_nodes_value[1]);
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
    free(sub_nodes_value);
    return result;
}
