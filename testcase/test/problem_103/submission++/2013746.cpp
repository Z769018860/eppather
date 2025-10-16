#include <stdio.h>
#include <string.h>

void get_next(char pattern[], int next[]) {
    int pattern_len = strlen(pattern);
    int i = 0, j = -1;
    next[0] = -1;

    while (i < pattern_len - 1) {
        if (j == -1 || pattern[i] == pattern[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

int kmp(char text[], char pattern[]) {
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);
    int next[pattern_len];
    int i = 0, j = 0;
    int cnt = 0;
    get_next(pattern, next);

    while (i < text_len) {
        if (j == -1 || text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }

        if (j == pattern_len) {
            cnt++;
            j = next[j - 1] + 1;
        }
    }

    return cnt;
}

int main() {
    char text[1000005], pattern[1000005];
    scanf("%s", text);
    scanf("%s", pattern);

    int result = kmp(text, pattern);

    printf("%d", result);

    return 0;
}
