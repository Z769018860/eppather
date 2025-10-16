void Insert_sort(int ar[5], int len) {
    int temp = 0;
    int i, j;

    for(i = 1; i < len; i = i + 1) {
        if(ar[i] < ar[i-1]) {
            temp = ar[i];
            for(j = i - 1; j >= 0 && ar[j] > temp; j = j - 1) {
                ar[j + 1] = ar[j];
            }
            ar[j + 1] = temp;
        }
        ;
    }
    return;
}
