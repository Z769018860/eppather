#include <cstdio>
inline long long read() {
    char c;
    long long x;
    while ((c = getchar()) < '0' || c > '9')
        ;
    x = c ^ '0';
    while ((c = getchar()) <= '9' && c >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
    return x;
}
int main() {
    int T = read();
    while (T--) {
        long long n = read();
        puts(n >= 4 ? "Yes" : "No");
        puts(n >= 4 && ~n & 1 ? "Yes" : "No");
    }
}