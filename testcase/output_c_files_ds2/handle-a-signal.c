void handleSigint(int gotint[5]) {
    gotint[0] = 1;
}

void func() {
    int gotint[5] = {0};
    int i[5] = {0};
    int startTime[5] = {0};
    int endTime[5] = {0};
    int td[5] = {0};
    
    handleSigint(gotint);
    
    for (int j = 0; j < 5; j = j + 1) {
        if (gotint[0] != 0) {
            break;
        }
        if (gotint[0] != 0) {
            break;
        }
        i[0] = i[0] + 1;
    }
    
    td[0] = (endTime[0] - startTime[0]) / 1000000;
    return;
}
