#include "mathex.h"

double factorial(double x) {
    if (x == 0.0) {
        return 1.0;
    }
    return x * factorial(x - 1);
}
