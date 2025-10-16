#include <regex.h>
char p[101], s[101];
regmatch_t m[1];
regex_t r;
int main() {
    while (~scanf("%s%s", p, s))
        regcomp(&r, p, 1), puts(regexec(&r, s, 1, m, 0) || m->rm_eo - m->rm_so < strlen(s) ? "No" : "Yes"),
            regfree(&r);
}
