int func() {
    int arr[7] = {1,2,1,0,2,0,2,0};
    int i;
    int j;
    int count;
    
    for (i = 0; i < 7; i = i + 1) {
        count = 1;
        for (j = i + 1; j < 7; j = j + 1) {
            if (arr[i] == arr[j]) {
                count = count + 1;
            }
        }
        if (count == arr[i]) {
            continue;
        } else {
            break;
        }
    }
    return;
}
