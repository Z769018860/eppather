#include <stdio.h>
char s[1919810];
int main()
{
    FILE *in = freopen("copycat.in", "r", stdin), *out = freopen("copycat.out", "w", stdout);
    int len = fread(s, 1, 1919810, stdin);
    int idx = 0;
    while (s[idx] != '\n')
        ++idx;
    ++idx;
    while (idx < len)
        putchar_unlocked(s[idx++]);
    fclose(in), fclose(out);
}