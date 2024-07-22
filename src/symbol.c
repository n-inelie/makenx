#include "makenx.h"
#include <string.h>

Symbol GetSymbol(char *str) {
    if (strncmp(str, "add", 3) == 0) {
        return ADD;
    } else if (strncmp(str, "mul", 3) == 0) {
        return MULTIPLY;
    } else if (strncmp(str, "sub", 3) == 0) {
        return SUBTRACT;
    } else if (strncmp(str, "div", 3) == 0) {
        return DIVIDE;
    } else if (strncmp(str, "pow", 3) == 0) {
        return POW;
    } else if (strncmp(str, "fact", 4) == 0) {
        return FACT;
    } else if (strncmp(str, "ln", 2) == 0) {
        return LN;
    } else if (strncmp(str, "log", 3) == 0) {
        return LOG;
    } else if (strncmp(str, "log10", 5) == 0) {
        return LOG10;
    } else if (strncmp(str, "log2", 4) == 0) {
        return LOG2;
    } else if (strncmp(str, "logab", 5) == 0) {
        return LOGAB;
    } else if (strncmp(str, "sin", 3) == 0) {
        return SIN;
    } else if (strncmp(str, "cos", 3) == 0) {
        return COS;
    } else if (strncmp(str, "tan", 3) == 0) {
        return TAN;
    } else if (strncmp(str, "period", 6) == 0) {
        return PERIOD;
    } else {
        return VARIABLE;
    }
}
