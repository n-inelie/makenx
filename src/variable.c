#include "makenx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

inline bool are_var_equal(Var v1, Var v2) {
    if (strcmp(v1.name, v2.name) == 0) {
        return true;
    }
    return false;
}

inline int does_var_exist(VarStack *v_stack, char *name) {
    Var v;
    for (size_t i = 0; i < v_stack->size; ++i) {
        v = v_stack->vars[i];
        if (strcmp(v.name, name) == 0) {
            return i;
        }
    }
    return -1;
}

inline double get_var_value(VarStack *v_stack, char *name) {
    Var v;
    for (size_t i = 0; i < v_stack->size; ++i) {
        v = v_stack->vars[i];
        if (strcmp(name, v.name) == 0) {
            return v.value;
        }
    }
    fprintf(stderr, "Error: (dev) Could not fine variable %s\n", name);
    exit(EXIT_FAILURE);
}

inline void set_var_value(VarStack *v_stack, char *name, double value) {
    int index = does_var_exist(v_stack, name);
    if (index == -1) {
        fprintf(stderr, "Error: (dev) Var %s does not exist\n", name);
    }
    v_stack->vars[index].value = value;
}

inline bool are_all_var_set(VarStack *v_stack) {
    for (size_t i = 0; i < v_stack->size; ++i) {
        if (isnan(v_stack->vars[i].value)) {
            return false;
        }
    }
    return true;
}
