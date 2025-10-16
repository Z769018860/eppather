void powers(int gen_given[5], int gen_taker[5], int gen_giver[5], int m) {
    int base[5];
    int exponent[5];
    int n[5];
    int result[5];
    
    for (n[0] = 0; n[0] < 5; n[0] = n[0] + 1) {
        base[0] = n[0];
        exponent[0] = m;
        result[0] = 1;
        for (; exponent[0] != 0; exponent[0] = exponent[0] >> 1) {
            if (exponent[0] & 1) {
                result[0] = result[0] * base[0];
            }
            base[0] = base[0] * base[0];
        }
        gen_given[0] = result[0];
    }
    return;
}

void squares_without_cubes(int gen_given[5], int gen_taker[5], int gen_giver[5]) {
    int cubes_given[5];
    int cubes_taker[5];
    int cubes_giver[5];
    int squares_given[5];
    int squares_taker[5];
    int squares_giver[5];
    int c[5];
    int s[5];
    
    powers(cubes_given, cubes_taker, cubes_giver, 3);
    c[0] = cubes_given[0];
    
    powers(squares_given, squares_taker, squares_giver, 2);
    s[0] = squares_given[0];
    
    for (;;) {
        for (; c[0] < s[0]; c[0] = cubes_given[0]) {
            powers(cubes_given, cubes_taker, cubes_giver, 3);
        }
        if (c[0] != s[0]) {
            gen_given[0] = s[0];
        }
        s[0] = squares_given[0];
        powers(squares_given, squares_taker, squares_giver, 2);
    }
    return;
}
