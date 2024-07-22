#include "makenx.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

inline size_t hash(char *str) {
    char first_char = tolower(str[0]);
    char last_char = tolower(str[strlen(str) - 1]);
    return (first_char * last_char) % 1024; 
}

static inline void addMapItem(char *str, Symbol sym) {
    size_t index = hash(str);
    OMap[index] = sym;
}

void initOMap(void) {
    addMapItem("period", PERIOD);
    addMapItem("add", ADD);
    addMapItem("mul", MULTIPLY);
    addMapItem("sub", SUBTRACT);
    addMapItem("div", DIVIDE);
    addMapItem("pow", POW);
    addMapItem("fact", FACT);
    addMapItem("ln", LN);
    addMapItem("log10", LOG10);
    addMapItem("log2", LOG2);
    addMapItem("logab", LOGAB);
    addMapItem("sin", SIN);
    addMapItem("cos", COS);
    addMapItem("tan", TAN);
}

