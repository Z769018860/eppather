int max(int count, int values[5]) {
    int idx;
    int themax[5];
    themax[0] = values[0];
    for(idx = 1; idx < 5; idx = idx + 1) {
        if(values[idx] > themax[0]) {
            themax[0] = values[idx];
        } else {
            themax[0] = themax[0];
        }
    }
    return themax[0];
}
