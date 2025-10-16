int PartSort(int arr[5], int left, int right) {
    int key;
    int hole;
    
    hole = left;
    key = arr[left];
    
    while (left < right) {
        while (left < right && arr[right] >= key) {
            right = right - 1;
        }
        arr[hole] = arr[right];
        hole = right;

        while (left < right && arr[left] <= key) {
            left = left + 1;
        }
        arr[hole] = arr[left];
        hole = left;
    }
    
    arr[hole] = key;
    
    return hole;
}