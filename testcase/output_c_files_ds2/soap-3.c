void anotherSoapFunc(int n1, int n2) {
    int x[5];
    for (x[0] = 0; x[0] < 5; x[0] = x[0] + 1) {
        if (n1 > n2) {
            x[1] = n1;
        } else {
            x[1] = n2;
        }
    }
    return;
}
