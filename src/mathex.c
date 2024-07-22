#include "mathex.h"
#include <math.h>

inline double period(double x, double y) {
    if (y < 10) {
        return x + y / 10;
    }
    return x + y / ceil(log10(y));
}

inline double factorial(double x) {
    if (x == 0.0) {
        return 1.0;
    }
    return x * factorial(x - 1);
}
