void rewrite_function(int n1, int n2, int n3, int n4, int n5) {
    int arr1[5];
    int arr2[5];
    int arr3[5];
    int arr4[5];
    int arr5[5];
    
    for (int i = 0; i < 5; i = i + 1) {
        arr1[i] = 0;
        arr2[i] = 0;
        arr3[i] = 0;
        arr4[i] = 0;
        arr5[i] = 0;
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (n1 > n2) {
            arr1[i] = arr1[i] + 1;
        } else {
            arr2[i] = arr2[i] + 1;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (n3 < n4) {
            arr3[i] = arr3[i] + 1;
        } else {
            arr4[i] = arr4[i] + 1;
        }
    }
    
    for (int i = 0; i < 5; i = i + 1) {
        if (n5 == 0) {
            arr5[i] = arr5[i] + 1;
        }
    }
    
    return;
}
