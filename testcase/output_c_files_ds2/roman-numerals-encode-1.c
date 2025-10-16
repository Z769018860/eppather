void roman(char *s, int n) {
    int n1;
    n1 = 1000;
    int n2;
    n2 = 900;
    int n3;
    n3 = 500;
    int n4;
    n4 = 400;
    int n5;
    n5 = 100;
    int n6;
    n6 = 90;
    int n7;
    n7 = 50;
    int n8;
    n8 = 40;
    int n9;
    n9 = 10;
    int n10;
    n10 = 9;
    int n11;
    n11 = 5;
    int n12;
    n12 = 4;
    int n13;
    n13 = 1;
    
    for (; n >= n1; n = n - n1) {
        *s = 77;
        s = s + 1;
    }
    if (n >= n2) {
        *s = 67;
        s = s + 1;
        *s = 77;
        s = s + 1;
        n = n - n2;
    }
    if (n >= n3) {
        *s = 68;
        s = s + 1;
        n = n - n3;
    }
    if (n >= n4) {
        *s = 67;
        s = s + 1;
        *s = 68;
        s = s + 1;
        n = n - n4;
    }
    for (; n >= n5; n = n - n5) {
        *s = 67;
        s = s + 1;
    }
    if (n >= n6) {
        *s = 88;
        s = s + 1;
        *s = 67;
        s = s + 1;
        n = n - n6;
    }
    if (n >= n7) {
        *s = 76;
        s = s + 1;
        n = n - n7;
    }
    if (n >= n8) {
        *s = 88;
        s = s + 1;
        *s = 76;
        s = s + 1;
        n = n - n8;
    }
    for (; n >= n9; n = n - n9) {
        *s = 88;
        s = s + 1;
    }
    if (n >= n10) {
        *s = 73;
        s = s + 1;
        *s = 88;
        s = s + 1;
        n = n - n10;
    }
    if (n >= n11) {
        *s = 86;
        s = s + 1;
        n = n - n11;
    }
    if (n >= n12) {
        *s = 73;
        s = s + 1;
        *s = 86;
        s = s + 1;
        n = n - n12;
    }
    for (; n >= n13; n = n - n13) {
        *s = 73;
        s = s + 1;
    }
    *s = 0;
    return;
}
