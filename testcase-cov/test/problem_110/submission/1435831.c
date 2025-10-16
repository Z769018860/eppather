#include<stdio.h>
long long Quick_Pow(long long n, long long m, long long P) {
    int sum = 1;
    while (m) {
        if (m & 1)sum=(sum*n)%P;
        n = (n * n) % P;
        m >>= 1;
    }
    return sum;
}


int main() {
    long long n, P;
    scanf("%lld %lld", &n, &P);
    for (int i = 1; i <= n; i++) {

        printf("%lld\n", Quick_Pow(i, P - 2, P));

    }



    return 0;
}