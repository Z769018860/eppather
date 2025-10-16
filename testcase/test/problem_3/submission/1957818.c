#include <stdio.h>
#include <stdlib.h>

int main() {
    
    FILE *inputFile = fopen("copycat.in", "r");

    
    if (inputFile == NULL) {
        printf("无法打开输入文件 copycat.in\n");
        return 1; 
    }

    
    FILE *outputFile = fopen("copycat.out", "w");

    
    if (outputFile == NULL) {
        printf("无法打开输出文件 copycat.out\n");
        fclose(inputFile); 
        return 1; 
    }

    
    int T;
    fscanf(inputFile, "%d", &T);

    
    for (int i = 0; i < T; ++i) {
        char buffer[10010];  
        fscanf(inputFile, "%s", buffer);
        fprintf(outputFile, "%s\n", buffer);
    }

    
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}