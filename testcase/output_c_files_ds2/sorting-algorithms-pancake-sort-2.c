void do_flip(int* list, int length, int num) {
    int swap[5];
    int i[5];
    i[0] = 0;
    num = num - 1;
    for (i[0] = 0; i[0] < num; i[0] = i[0] + 1) {
        swap[0] = list[i[0]];
        list[i[0]] = list[num];
        list[num] = swap[0];
        num = num - 1;
    }
    return;
}
