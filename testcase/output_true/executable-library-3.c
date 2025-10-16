int hailstone_sequence(int n, int dummy) {
    int count = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        count = count + 1;
    }
    return count;
}

void find_longest_hailstone() {
    int i[5];
    int longest[5];
    int longest_i[5];
    int len[5];
    
    longest[0] = 0;
    for (i[0] = 1; i[0] < 5; i[0] = i[0] + 1) {
        len[0] = hailstone_sequence(i[0], 0);
        if (len[0] > longest[0]) {
            longest_i[0] = i[0];
            longest[0] = len[0];
        }
    }
    return;
}
