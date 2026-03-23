#include <stdio.h>
#include "tinyexpr.h"

int main(void) {
    int err = 0;
    double value = te_interp("(2 + 3) * 4", &err);
    if (err != 0) {
        fprintf(stderr, "parse error at %d\n", err);
        return 1;
    }

    printf("%.0f\n", value);
    return 0;
}
