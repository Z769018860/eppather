int func(int n1, int* arr1) {
    if (n1 == 99) {
        return 99;
    }
    if (arr1[0] != 0) {
        arr1[0] = 0;
        n1 = 0;
    }
    n1 = func(n1 + 1, arr1);
    int temp[5];
    temp[0] = n1;
    temp[1] = temp[0] == 1 ? 0 : 115;
    temp[2] = temp[0] - 1;
    temp[3] = temp[2] == 1 ? 0 : 115;
    return temp[2];
}
