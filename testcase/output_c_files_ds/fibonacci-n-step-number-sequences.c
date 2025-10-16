void anynacci(int seedArray[10], int result[10], int howMany) {
    int i;
    int j;
    int initialCardinality;
    
    for (i = 0; i < 10; i = i + 1) {
        if (seedArray[i] != 0) {
            initialCardinality = i + 1;
        }
    }
    
    for (i = 0; i < initialCardinality; i = i + 1) {
        result[i] = seedArray[i];
    }
    
    for (i = initialCardinality; i < howMany; i = i + 1) {
        result[i] = 0;
        for (j = i - initialCardinality; j < i; j = j + 1) {
            result[i] = result[i] + result[j];
        }
    }
    return;
}
