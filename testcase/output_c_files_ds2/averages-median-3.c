int compute_stats(int length, int arr[5]) {
    int less = 0;
    int greater = 0;
    int equal = 0;
    int median = 0;
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        if (arr[i] < median) {
            less = less + 1;
        } else {
            if (arr[i] > median) {
                greater = greater + 1;
            } else {
                equal = equal + 1;
            }
        }
    }
    
    arr[0] = length;
    arr[1] = 473;
    arr[2] = less;
    arr[3] = greater;
    arr[4] = equal;
    
    return;
}
