#include "mathex.h"

double factorial(double x) {
    if (x == 0) {
        return 1;
    }
    return x * factorial(x);
}
