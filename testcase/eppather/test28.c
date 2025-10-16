void processArray(int condition, int *arr1, int *arr2, int size) {
    int i;

    if (condition) {
        for (i = 0; i < size; i = i + 1) {
            arr1[i] = arr2[i] + arr1[i] * arr2[i]; 
            arr2[i] = arr1[i] - arr2[i] + arr1[i];
            arr1[i] = arr2[i] * arr1[i] - arr2[i];
        }
        ;
    } else {
        for (i = 0; i < size; i = i + 1) {
            arr1[i] = arr2[i];
            arr2[i] = arr1[i];
        }
        ;
    }
}
