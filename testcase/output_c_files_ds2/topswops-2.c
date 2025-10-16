void tryswaps(int a_v[16], int f, int s, int d, int best_n, int n1) {
    int b_v[16];
    int t;
    int j;
    int x;
    int spin;
    int continue_flag;
    
    while (1) {
        if (best_n < d) {
            t = best_n;
            continue_flag = 0;
            if (best_n != t) {
                spin = 64;
                for (; spin != 0; spin = spin - 1) { }
                continue;
            }
            best_n = d;
        }
        break;
    }

    x = 15 - s;
    if (x == 0) {
        if ((a_v[15] == 15 || (a_v[15] == -1 && !(f & 32768))) && (a_v[15] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 14;
        }
    } else if (x == 1) {
        if ((a_v[14] == 14 || (a_v[14] == -1 && !(f & 16384))) && (a_v[14] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 13;
        }
    } else if (x == 2) {
        if ((a_v[13] == 13 || (a_v[13] == -1 && !(f & 8192))) && (a_v[13] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 12;
        }
    } else if (x == 3) {
        if ((a_v[12] == 12 || (a_v[12] == -1 && !(f & 4096))) && (a_v[12] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 11;
        }
    } else if (x == 4) {
        if ((a_v[11] == 11 || (a_v[11] == -1 && !(f & 2048))) && (a_v[11] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 10;
        }
    } else if (x == 5) {
        if ((a_v[10] == 10 || (a_v[10] == -1 && !(f & 1024))) && (a_v[10] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 9;
        }
    } else if (x == 6) {
        if ((a_v[9] == 9 || (a_v[9] == -1 && !(f & 512))) && (a_v[9] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 8;
        }
    } else if (x == 7) {
        if ((a_v[8] == 8 || (a_v[8] == -1 && !(f & 256))) && (a_v[8] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 7;
        }
    } else if (x == 8) {
        if ((a_v[7] == 7 || (a_v[7] == -1 && !(f & 128))) && (a_v[7] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 6;
        }
    } else if (x == 9) {
        if ((a_v[6] == 6 || (a_v[6] == -1 && !(f & 64))) && (a_v[6] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 5;
        }
    } else if (x == 10) {
        if ((a_v[5] == 5 || (a_v[5] == -1 && !(f & 32))) && (a_v[5] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 4;
        }
    } else if (x == 11) {
        if ((a_v[4] == 4 || (a_v[4] == -1 && !(f & 16))) && (a_v[4] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 3;
        }
    } else if (x == 12) {
        if ((a_v[3] == 3 || (a_v[3] == -1 && !(f & 8))) && (a_v[3] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 2;
        }
    } else if (x == 13) {
        if ((a_v[2] == 2 || (a_v[2] == -1 && !(f & 4))) && (a_v[2] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 1;
        }
    } else if (x == 14) {
        if ((a_v[1] == 1 || (a_v[1] == -1 && !(f & 2))) && (a_v[1] == -1 || d + best_n >= best_n)) {
        } else {
            if (d + best_n <= best_n) {
                return;
            }
            s = 0;
        }
    } else {
        return;
    }

    for (x = 0; x < 16; x = x + 1) {
        b_v[x] = a_v[x];
    }
    d = d + 1;

    for (x = 1; x <= 15; x = x + 1) {
        if (a_v[x] == x || ((a_v[x] == -1) && !(f & (1 << x)))) {
            b_v[0] = x;
            for (j = x; j != 0; j = j - 1) {
                b_v[x - (j - 1)] = a_v[j - 1];
            }
            tryswaps(b_v, f | (1 << x), s, d, best_n, n1);
        }
        if (s == x) {
            return;
        }
    }
    return;
}
