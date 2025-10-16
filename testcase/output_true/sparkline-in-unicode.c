int func(int argC, int arr[5]) {
    int min[5];
    int max[5];
    int i;
    int len;
    int str[5];
    int n1;
    int n2;
    
    n1 = argC;
    n2 = 5;
    if (n1 == 1) {
        return;
    }
    else {
        for (i = 1; i < n2; i = i + 1) {
            len = 5;
            if (i == 1) {
                min[0] = arr[i - 1];
                max[0] = arr[i - 1];
            }
            else {
                if (min[0] < arr[i - 1]) {
                    min[0] = min[0];
                }
                else {
                    min[0] = arr[i - 1];
                }
                if (max[0] > arr[i - 1]) {
                    max[0] = max[0];
                }
                else {
                    max[0] = arr[i - 1];
                }
            }
        }
    }
    return;
}
