int run(int v, char *s) {
    int val = v;
    int fractions[14][2] = {{17,91},{78,85},{19,51},{23,38},{29,33},{77,29},{95,23},{77,19},{1,17},{11,13},{13,11},{15,14},{15,2},{55,1}};
    int count = 14;
    int i;
    int temp;
    int power_of_two;

loop:
    temp = val;
    power_of_two = 0;
    if (temp != 0) {
        while ((temp & 1) == 0) {
            temp = temp >> 1;
            power_of_two = power_of_two + 1;
        }
    }
    if (temp == 1) {
    } else {
    }

    for (i = 0; i < count; i = i + 1) {
        if (val % fractions[i][1] != 0) {
            continue;
        }
        val = val / fractions[i][1];
        val = val * fractions[i][0];
        goto loop;
    }

    return 0;
}
