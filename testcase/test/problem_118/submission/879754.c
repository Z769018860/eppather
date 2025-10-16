#include <stdio.h>
#include <string.h>
#include <regex.h>

char regex[110], str[110];
int main() {
    while (~scanf("%s%s", regex, str)) {
        regex_t reg;
        regcomp(&reg, regex, REG_EXTENDED);
        regmatch_t rgm[1];
        if (regexec(&reg, str, 1, rgm, 0) == 0) {
            if (rgm[0].rm_eo - rgm[0].rm_so == strlen(str))
                printf("Yes\n");
            else
                printf("No\n");
        } else
            printf("No\n");
    }
    return 0;
}