int mid3(int n, char buf[32], int* result) {
    int num = n;
    if (num < 0) {
        num = -num;
    }
    int len = 0;
    int temp = num;
    for (; temp != 0; len = len + 1) {
        temp = temp / 10;
    }
    if (len < 3 || (len % 2) == 0) {
        return 0;
    }
    int pos = len / 2 - 1;
    temp = num;
    int i = 0;
    for (i = 0; i < len; i = i + 1) {
        buf[len - 1 - i] = (temp % 10) + '0';
        temp = temp / 10;
    }
    buf[pos + 3] = '\0';
    for (i = 0; i < 3; i = i + 1) {
        result[i] = buf[pos + i];
    }
    return 1;
}
