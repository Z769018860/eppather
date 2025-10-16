int Query(int Data[5], int Length[5]) {
    int message[5] = {'H', 'e', 'r', 'e', ' '};
    int n = 5;
    int i;
    if (n <= Length[0]) {
        for (i = 0; i < n; i = i + 1) {
            Data[i] = message[i];
        }
        Length[0] = n;
        return 1;
    }
    return 0;
}
