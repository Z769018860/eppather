void func(int depth) {
    int i;
    int j;
    int d;
    int dim;
    int n;
    int arr[5];
    int arr1[5];
    int arr2[5];
    int arr3[5];
    int arr4[5];
    
    dim = 1;
    for (i = 0; i < depth; i = i + 1) {
        dim = dim * 3;
    }
    
    for (i = 0; i < dim; i = i + 1) {
        for (j = 0; j < dim; j = j + 1) {
            d = dim / 3;
            arr[0] = 0;
            for (n = 0; n < 5; n = n + 1) {
                if (d) {
                    arr1[0] = i % (d * 3);
                    arr1[0] = arr1[0] / d;
                    arr2[0] = j % (d * 3);
                    arr2[0] = arr2[0] / d;
                    if (arr1[0] == 1 && arr2[0] == 1) {
                        arr[0] = 1;
                        break;
                    }
                    d = d / 3;
                }
            }
            if (arr[0]) {
                arr3[0] = 0;
            } else {
                arr4[0] = 0;
            }
        }
    }
    return;
}
