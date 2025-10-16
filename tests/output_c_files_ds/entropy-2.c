int entropy(char input[256]) {
    int counts[256];
    int length;
    int i;
    int j;
    double result;
    double temp;
    double log2;
    
    for (i = 0; i < 256; i = i + 1) {
        counts[i] = 0;
    }
    
    length = 0;
    for (i = 0; input[i] != 0; i = i + 1) {
        counts[input[i]] = counts[input[i]] + 1;
        length = length + 1;
    }
    
    result = 0.0;
    for (i = 0; i < 256; i = i + 1) {
        if (counts[i] > 0) {
            temp = (double)counts[i] / (double)length;
            log2 = 0.0;
            for (j = counts[i]; j > 0; j = j / 2) {
                log2 = log2 + 1.0;
            }
            log2 = log2 - 1.0;
            result = result - temp * (log2 / 1.4426950408889634);
        }
    }
    
    return (int)(result * 1000000);
}
