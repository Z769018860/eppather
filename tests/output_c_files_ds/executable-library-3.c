int hailstone_sequence() {
    int i;
    int longest;
    int longest_i;
    int len;
    int temp;
    
    longest = 0;
    longest_i = 0;
    for (i = 1; i < 100000; i = i + 1) {
        temp = i;
        len = 1;
        while (temp != 1) {
            if (temp % 2 == 0) {
                temp = temp / 2;
            } else {
                temp = 3 * temp + 1;
            }
            len = len + 1;
        }
        if (len > longest) {
            longest_i = i;
            longest = len;
        }
    }
    return longest_i;
}
