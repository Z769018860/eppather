void selectSort(int data[5], int n) {
    int min;
    int i, j;
    int temp;

    for(i = 0; i < n - 1; i = i + 1) {
        min = i;
        for(j = i + 1; j < n; j = j + 1) {
            if(data[j] < data[min]) {
                min = j;
            }
        }

        if(data[i] != data[min]) {
            temp = data[i];
            data[i] = data[min];
            data[min] = temp;
        }
        ;
    }
}
