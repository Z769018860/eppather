#include<stdio.h>
#include<string.h>

int n;
char s[2002000];
int main(){
	scanf("%s",s);
	n = strlen(s);

    
    
    
    for (int i = 0, j = 0, k = 1; i < n;) {
        
        if (k > n || s[j] > s[k]) {
            for(; i <= j; i += k - j)
                printf("%d ", i + k - j);
            j = i;
            k = i + 1;
        }
        else if (s[j] < s[k]) j = i, k++;
        else j++, k++;
    }
}