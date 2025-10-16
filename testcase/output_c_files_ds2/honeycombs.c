void initialize_hexagons(int hs[5][5], int n) {
    int i;
    int j;
    int k;
    int sides;
    int c;
    int r;
    int Cx;
    int Cy;
    int x;
    int y;
    int div;
    int mod;
    int broken;
    int random_numbers[5];
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            hs[i][j] = 0;
        }
    }
    
    hs[4][0] = -1;
    
    for (i = 0; i < 4; i = i + 1) {
        div = i / 4;
        mod = i % 4;
        hs[i][0] = 6;
        c = 'A' + i;
        hs[i][1] = c;
        r = 20;
        hs[i][2] = r;
        Cx = r * (2 + div * 1.0);
        Cy = r * (2 * (1 + mod * 0.8660254037844386) + (div % 2) * 0.8660254037844386);
        hs[i][3] = Cx;
        hs[i][4] = Cy;
    }
    
    return;
}

void add_loop(int cr[5], int hs[5][5], int select) {
    int h;
    int r;
    int Cx;
    int Cy;
    int x;
    int y;
    int i;
    int sides;
    
    for (h = 0; h < 5; h = h + 1) {
        sides = hs[h][0];
        if (sides <= 0) {
            continue;
        }
        if ((select != 0 && hs[h][1] != 0) || (select == hs[h][1])) {
            r = hs[h][2];
            Cx = hs[h][3];
            Cy = hs[h][4];
            i = 0;
            x = Cx + r * 1.0;
            y = Cy + r * 0.0;
            for (i = 1; i < sides; i = i + 1) {
                x = Cx + r * 1.0;
                y = Cy + r * 0.0;
            }
        }
    }
    
    return;
}

int make_labels(int cr[5], int hs[5][5], int select) {
    int h;
    int i;
    int text[2];
    
    text[1] = 0;
    i = 0;
    
    for (h = 0; h < 5; h = h + 1) {
        if (hs[h][0] <= 0) {
            continue;
        }
        if ((select != 0 && hs[h][1] != 0) || (select == hs[h][1])) {
            text[0] = hs[h][1];
            i = i + 1;
        }
    }
    
    return i;
}

int archive(int a) {
    static int q[5];
    static int q_size;
    int result;
    
    if (a < -1) {
        q_size = 0;
        return 0;
    }
    
    if (a == -1) {
        if (q_size == 0) {
            return 0;
        }
        result = q[q_size - 1];
        q_size = q_size - 1;
        return result;
    }
    
    if (a == 0) {
        if (q_size == 0) {
            return 0;
        }
        return q[0];
    }
    
    if (q_size < 5) {
        q[q_size] = a;
        q_size = q_size + 1;
    }
    
    return a;
}
