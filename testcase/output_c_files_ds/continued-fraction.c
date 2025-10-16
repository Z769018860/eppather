int calc(int f_a_type, int f_b_type, int expansions) {
    int a;
    int b;
    int r;
    a = 0;
    b = 0;
    r = 0;
    
    int i;
    for (i = expansions; i > 0; i = i - 1) {
        if (f_a_type == 1) {
            if (i != 0) {
                a = 2;
            } else {
                a = 1;
            }
        } else if (f_a_type == 2) {
            if (i != 0) {
                a = i;
            } else {
                a = 2;
            }
        } else if (f_a_type == 3) {
            if (i != 0) {
                a = 6;
            } else {
                a = 3;
            }
        }
        
        if (f_b_type == 1) {
            b = 1;
        } else if (f_b_type == 2) {
            if (i > 1) {
                b = i - 1;
            } else {
                b = 1;
            }
        } else if (f_b_type == 3) {
            int c;
            c = 2 * i - 1;
            b = c * c;
        }
        
        r = b / (a + r);
    }
    
    if (f_a_type == 1) {
        a = 1;
    } else if (f_a_type == 2) {
        a = 2;
    } else if (f_a_type == 3) {
        a = 3;
    }
    
    return a + r;
}
