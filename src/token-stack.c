#include "makenx.h"
#include <stdlib.h>
#include <stdio.h>

TokenStack *create_token_stack(size_t reserve) {
    TokenStack *t_stack = calloc(1, sizeof(*t_stack));
    t_stack->tokens = calloc(reserve, sizeof(Token));
    t_stack->capacity = reserve;
    return t_stack;
}

void destroy_token_stack(TokenStack *t_stack) {
    free(t_stack->tokens);
    free(t_stack);
}

void append_token(TokenStack *t_stack, Token t) {
    if (t_stack->size == t_stack->capacity) {
        if (t_stack->capacity < 16) {
            t_stack->capacity *= 2;
        } else {
            t_stack->capacity *= 1.5;
        }
        t_stack->tokens =
            reallocarray(t_stack->tokens, t_stack->capacity, sizeof(Token));
        if (t_stack->tokens == NULL) {
            fprintf(stderr, "Error: Failed to append token\n");
            exit(EXIT_FAILURE);
        }
    }
    t_stack->tokens[t_stack->size] = t;
    ++(t_stack->size);
}
