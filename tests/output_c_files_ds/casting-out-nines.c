#include <stdio.h>
#include <math.h>

int main() {
    const int N = 2;
    int base = 10;
    c1 = 0;
    c2 = 0;
    k;

    for (k =1; k < pow(base, N); k++) {
        c1++;
        if (k % (base - 1) == (k * k) % (base - 1) {
            c2++;
            printf("%d ", k);
        }
    }

    printf("\nTring %d numbers instead of %d numbers saves %f%%\b", c2, c1, 100.0 - 100.0 c2 / c1);
    return 0;
}
