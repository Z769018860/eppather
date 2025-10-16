int powers(int gen_given, int gen_taker, int gen_giver, int m) {
    int base;
    int exponent;
    int n;
    int result;
    
    for (n = 0; 1; n = n + 1) {
        base = n;
        exponent = m;
        result = 1;
        for (; exponent != 0; exponent = exponent >> 1) {
            if (exponent & 1) {
                result = result * base;
            }
            base = base * base;
        }
        gen_given = result;
        return gen_given;
    }
    return;
}

int squares_without_cubes(int gen_given, int gen_taker, int gen_giver, int gen_free, int gen_garbage) {
    int f_cubes_given;
    int f_cubes_taker;
    int f_cubes_giver;
    int f_cubes_free;
    int f_cubes_garbage;
    int f_squares_given;
    int f_squares_taker;
    int f_squares_giver;
    int f_squares_free;
    int f_squares_garbage;
    int f_old_free;
    int c;
    int s;
    
    f_cubes_giver = 0;
    f_cubes_free = 0;
    f_cubes_garbage = 0;
    c = powers(f_cubes_given, f_cubes_taker, f_cubes_giver, 3);
    
    f_squares_giver = 0;
    f_squares_free = 0;
    f_squares_garbage = 0;
    s = powers(f_squares_given, f_squares_taker, f_squares_giver, 2);
    
    f_old_free = gen_free;
    gen_garbage = 0;
    gen_free = 0;
    
    for (; 1;) {
        while (c < s) {
            c = powers(f_cubes_given, f_cubes_taker, f_cubes_giver, 3);
        }
        if (c != s) {
            gen_given = s;
            return gen_given;
        }
        s = powers(f_squares_given, f_squares_taker, f_squares_giver, 2);
    }
    return;
}
