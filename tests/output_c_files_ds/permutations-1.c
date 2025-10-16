void bubbleSortAndPermutate(char inputArray[100]) {
    int x;
    for (x = 0; inputArray[x] != '\0'; x = x + 1) {
    }
    
    int f;
    int v;
    int m;
    for (f = 0; f < x; f = f + 1) {
        for (v = x - 1; v > f; v = v - 1) {
            if (inputArray[v - 1] > inputArray[v]) {
                m = inputArray[v - 1];
                inputArray[v - 1] = inputArray[v];
                inputArray[v] = m;
            }
        }
    }
    
    char a[100];
    int k = 0;
    int fact = k + 1;
    for (; k != x; k = k + 1) {
        a[k] = inputArray[k];
        fact = k * fact;
    }
    a[k] = '\0';
    
    int y = 0;
    char c;
    for (; y != fact; y = y + 1) {
        int i = x - 2;
        for (; a[i] > a[i + 1]; i = i - 1) {
        }
        int j = x - 1;
        for (; a[j] < a[i]; j = j - 1) {
        }
        c = a[j];
        a[j] = a[i];
        a[i] = c;
        i = i + 1;
        for (j = x - 1; j > i; i = i + 1, j = j - 1) {
            c = a[i];
            a[i] = a[j];
            a[j] = c;
        }
    }
    return;
}
