#include <stdio.h>
int main() {
    FILE *fp1, *fp2;
    fp1 = fopen("copycat.in", "r");
    fp2 = fopen("copycat.out", "w");
    short a, cnt = 0;
    while((a = getc(fp1)) != EOF) {
        if(cnt > 0) putc(a, fp2);
        if(a == '\n') cnt++;
    }
    return 0;
}