void initialize_hexagons(int hs[21][5], int n) {
    int i;
    int j;
    int k;
    int temp;
    int chars[26];
    int shuffled[26];
    int count;
    int div;
    int mod;
    
    for (i = 0; i < 26; i = i + 1) {
        chars[i] = 'A' + i;
    }
    
    count = 26;
    for (i = 0; i < 26; i = i + 1) {
        j = i + (i * 12345) % (26 - i);
        temp = chars[i];
        chars[i] = chars[j];
        chars[j] = temp;
    }
    
    for (i = 0; i < n; i = i + 1) {
        hs[i][0] = 0;
        hs[i][1] = 0;
        hs[i][2] = 20;
        hs[i][3] = 6;
        hs[i][4] = 0;
    }
    
    hs[n-1][3] = -1;
    
    for (i = 0; hs[i][3] != -1; i = i + 1) {
        div = i / 4;
        mod = i % 4;
        hs[i][4] = chars[i];
        hs[i][0] = 20 * (2 + div * 0.5);
        hs[i][1] = 20 * (2 * (1 + mod * 0.866) + (div % 2) * 0.866);
    }
    
    return;
}

void add_loop(int cr[100][100], int hs[21][5], int select) {
    int i;
    int j;
    int sides;
    double r;
    double Cx;
    double Cy;
    double x;
    double y;
    
    for (i = 0; hs[i][3] > 0; i = i + 1) {
        if ((select && hs[i][4]) || (select == hs[i][4])) {
            r = hs[i][2];
            Cx = hs[i][0];
            Cy = hs[i][1];
            sides = hs[i][3];
            x = Cx + r * 1.0;
            y = Cy;
            for (j = 1; j < sides; j = j + 1) {
                x = Cx + r * 0.5;
                y = Cy + r * 0.866;
            }
        }
    }
    return;
}

int make_labels(int cr[100][100], int hs[21][5], int select) {
    int i;
    int count;
    
    count = 0;
    for (i = 0; hs[i][3] > 0; i = i + 1) {
        if ((select && hs[i][4]) || (select == hs[i][4])) {
            count = count + 1;
        }
    }
    return count;
}

int archive(int a) {
    static int q[100];
    static int head;
    static int tail;
    static int size;
    
    if (a < -1) {
        head = 0;
        tail = 0;
        size = 0;
        return 0;
    }
    
    if (a == -1) {
        if (size == 0) {
            return 0;
        }
        tail = (tail + 99) % 100;
        size = size - 1;
        return q[tail];
    }
    
    if (a == 0) {
        if (size == 0) {
            return 0;
        }
        return q[head];
    }
    
    head = (head + 1) % 100;
    q[head] = a;
    size = size + 1;
    return a;
}

void draw(int widget[100][100], int cr[100][100], int data[21][5]) {
    add_loop(cr, data, 0);
    add_loop(cr, data, 1);
    if (make_labels(cr, data, 0) == 0) {
        int c;
        c = archive(-1);
        while (c != 0) {
            c = archive(-1);
        }
        archive(-2);
    }
    return;
}

void button_press_event(int widget[100][100], int event[10], int data[21][5]) {
    int i;
    double x_win;
    double y_win;
    double dx;
    double dy;
    double dist_sq;
    double r_sq;
    
    x_win = event[0];
    y_win = event[1];
    
    for (i = 0; data[i][3] > 0; i = i + 1) {
        dx = x_win - data[i][0];
        dy = y_win - data[i][1];
        dist_sq = dx * dx + dy * dy;
        r_sq = data[i][2] * data[i][2] * 0.75;
        if (dist_sq < r_sq) {
            data[i][4] = data[i][4] + 1;
            archive(data[i][4]);
            break;
        }
    }
    return;
}

void key_press_event(int widget[100][100], int event[10], int data[21][5]) {
    int i;
    int keyval;
    int unicode;
    
    keyval = event[0];
    unicode = keyval;
    
    for (i = 0; data[i][3] > 0; i = i + 1) {
        if (data[i][4] == unicode) {
            data[i][4] = data[i][4] + 1;
            archive(data[i][4]);
            break;
        }
    }
    return;
}
