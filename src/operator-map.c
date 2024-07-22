#include "makenx.h"
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

inline size_t hash(char *str) {
    char first_char = tolower(str[0]) - 65;
    char last_char = tolower(str[strlen(str) - 1]) - 65;
    return first_char + last_char;
}

static inline void addMapItem(char *str, Symbol sym) {
    OMap[hash(str)] = sym;
}

void initOMap(void) {
    addMapItem("add", ADD);
    addMapItem("mul", MULTIPLY);
    addMapItem("sub", SUBTRACT);
    addMapItem("div", DIVIDE);
    addMapItem("pow", POW);
}
