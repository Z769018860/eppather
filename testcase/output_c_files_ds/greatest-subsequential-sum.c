void maxSubseq(int sequence[11], int len, int result[3]) {
    int maxSum = 0;
    int thisSum = 0;
    int i = 0;
    int start = 0;
    int end = -1;
    int j;
    
    for (j = 0; j < len; j = j + 1) {
        thisSum = thisSum + sequence[j];
        if (thisSum < 0) {
            i = j + 1;
            thisSum = 0;
        } else {
            if (thisSum > maxSum) {
                maxSum = thisSum;
                start = i;
                end = j;
            }
        }
    }
    
    if (start <= end && start >= 0 && end >= 0) {
        result[0] = start;
        result[1] = end + 1;
        result[2] = maxSum;
    } else {
        result[0] = 0;
        result[1] = 0;
        result[2] = 0;
    }
    return;
}
