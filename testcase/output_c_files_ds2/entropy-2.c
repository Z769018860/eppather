void entropy(int input_len, char input[5]) {
    int freq[256];
    int i;
    int j;
    double total;
    double prob;
    double result;
    
    for (i = 0; i < 256; i = i + 1) {
        freq[i] = 0;
    }
    
    for (i = 0; i < input_len; i = i + 1) {
        freq[(int)input[i]] = freq[(int)input[i]] + 1;
    }
    
    total = 0.0;
    for (i = 0; i < 256; i = i + 1) {
        if (freq[i] > 0) {
            total = total + freq[i];
        }
    }
    
    result = 0.0;
    for (i = 0; i < 256; i = i + 1) {
        if (freq[i] > 0) {
            prob = freq[i] / total;
            result = result - prob * (prob > 0 ? log(prob) : 0);
        }
    }
    
    return;
}
