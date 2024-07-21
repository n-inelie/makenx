#include "makenx.h"
#include <string.h>

void parse(TokenStack *t_stack) {
    Token t;
    for (size_t i = 0; i < t_stack->size; ++i) {
        t = t_stack->tokens[i];
        switch(t.type) {
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
                break;
            case NUMERIC:
                break;
        }
    }
}