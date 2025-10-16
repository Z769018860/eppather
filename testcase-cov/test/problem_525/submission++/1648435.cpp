#include <cstdio>

int k;

int tmp, phi;

int main() {
    scanf("%d", &k);
    if (k == 1) {
        puts("-1");
        return 0;
    }
    tmp = phi = k;
    for (int i = 2; tmp > 1; i++)
        if (tmp % i == 0) {
            phi = phi * (i - 1) / i;
            while (tmp % i == 0)
                tmp /= i;
        }
    printf("%d\n", phi << 1);
    for (int i = 0; i < phi; i++)
        putchar(48), putchar(32);
    printf("%d ", k - 1);
    for (int i = phi + 1; i < (phi << 1); i++)
        putchar(48), putchar(32);
    putchar(49), putchar(10);
    return 0;
}