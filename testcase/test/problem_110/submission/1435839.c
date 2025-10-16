#include<stdio.h>

char ch;
 void read(long long* x) {
    *x = 0;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
    for (; ch >= '0' && ch <= '9'; ch = getchar())
        *x = (*x << 3) + (*x << 1) + (ch & 15);
}

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
    read(&n),read(&P);
    for (int i = 1; i <= n; i++) {

        printf("%lld\n", Quick_Pow(i, P - 2, P));

    }



    return 0;
}