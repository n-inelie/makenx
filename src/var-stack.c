#include "makenx.h"
#include <stdlib.h>
#include <stdio.h>

VarStack *create_var_stack(size_t reserve) {
    VarStack *v_stack = calloc(1, sizeof(*v_stack));
    v_stack->vars = calloc(reserve, sizeof(Var));
    v_stack->capacity = reserve;
    return v_stack;
}

void destroy_var_stack(VarStack *v_stack) {
    free(v_stack->vars);
    free(v_stack);
}

void append_var(VarStack *v_stack, Var t) {
    if (v_stack->size == v_stack->capacity) {
        if (v_stack->capacity < 16) {
            v_stack->capacity *= 2;
        } else {
            v_stack->capacity *= 1.5;
        }
        v_stack->vars =
            reallocarray(v_stack->vars, v_stack->capacity, sizeof(Var));
        if (v_stack->vars == NULL) {
            fprintf(stderr, "Error: Failed to append var\n");
            exit(EXIT_FAILURE);
        }
    }
    v_stack->vars[v_stack->size] = t;
    ++(v_stack->size);
}
