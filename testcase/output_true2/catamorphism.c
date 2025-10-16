int reduce(int (*fn)(int, int), int size, int *elms) {
    int val[5];
    int i;
    val[0] = elms[0];
    for (i = 1; i < size; i = i + 1) {
        val[0] = fn(val[0], elms[i]);
    }
    return val[0];
}

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

void combined() {
    int nums[5];
    nums[0] = 1;
    nums[1] = 2;
    nums[2] = 3;
    nums[3] = 4;
    nums[4] = 5;
    reduce(add, 5, nums);
    reduce(sub, 5, nums);
    reduce(mul, 5, nums);
    return;
}
