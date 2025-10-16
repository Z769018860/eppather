int func(int pointer[10]) {
    int array[10];
    pointer = array;
    pointer = &array[0];
    return;
}
