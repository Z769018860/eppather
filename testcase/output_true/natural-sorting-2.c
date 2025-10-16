void sort_flags(int flag1, int flag2, int flag3, int flag4, int flag5, int flag6) {
    int arr[5];
    arr[0] = flag1;
    arr[1] = flag2;
    arr[2] = flag3;
    arr[3] = flag4;
    arr[4] = flag5;
    
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 4; j = j + 1) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    return;
}
