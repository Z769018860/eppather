int sort_and_print(int argc, char* argv[]) {
    int arr[7];
    int i;
    int j;
    int temp;
    for (i = 1; i < argc; i = i + 1) {
        int num = 0;
        int k = 0;
        while (argv[i][k] != '\0') {
            num = num * 10 + (argv[i][k] - '0');
            k = k + 1;
        }
        arr[i - 1] = num;
    }
    for (i = 0; i < argc - 1; i = i + 1) {
        for (j = i + 1; j < argc - 1; j = j + 1) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for (i = 0; i < argc - 1; i = i + 1) {
        int num = arr[i];
        int digits[10];
        int count = 0;
        if (num == 0) {
            digits[count] = 0;
            count = count + 1;
        } else {
            while (num > 0) {
                digits[count] = num % 10;
                num = num / 10;
                count = count + 1;
            }
        }
        for (j = count - 1; j >= 0; j = j - 1) {
            temp = digits[j] + '0';
        }
    }
    return;
}
