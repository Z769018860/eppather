void tryswaps(int a[16], int f, int s, int d, int best[16], int n) {
    int b[16];
    int t;
    int j;
    int x;
    
    while (1) {
        t = best[n];
        if (best[n] == t) {
            if (best[n] < d) {
                best[n] = d;
            }
            break;
        }
    }
    
    x = 15 - s;
    if (x == 0) {
        if (!((a[15] == 15 || (a[15] == -1 && !(f & 1))) && (a[15] == -1 || d + best[15] >= best[n]))) {
            if (d + best[15] <= best[n]) {
                return;
            }
            s = 14;
        }
    } else if (x == 1) {
        if (!((a[14] == 14 || (a[14] == -1 && !(f & 2))) && (a[14] == -1 || d + best[14] >= best[n]))) {
            if (d + best[14] <= best[n]) {
                return;
            }
            s = 13;
        }
    } else if (x == 2) {
        if (!((a[13] == 13 || (a[13] == -1 && !(f & 4))) && (a[13] == -1 || d + best[13] >= best[n]))) {
            if (d + best[13] <= best[n]) {
                return;
            }
            s = 12;
        }
    } else if (x == 3) {
        if (!((a[12] == 12 || (a[12] == -1 && !(f & 8))) && (a[12] == -1 || d + best[12] >= best[n]))) {
            if (d + best[12] <= best[n]) {
                return;
            }
            s = 11;
        }
    } else if (x == 4) {
        if (!((a[11] == 11 || (a[11] == -1 && !(f & 16))) && (a[11] == -1 || d + best[11] >= best[n]))) {
            if (d + best[11] <= best[n]) {
                return;
            }
            s = 10;
        }
    } else if (x == 5) {
        if (!((a[10] == 10 || (a[10] == -1 && !(f & 32))) && (a[10] == -1 || d + best[10] >= best[n]))) {
            if (d + best[10] <= best[n]) {
                return;
            }
            s = 9;
        }
    } else if (x == 6) {
        if (!((a[9] == 9 || (a[9] == -1 && !(f & 64))) && (a[9] == -1 || d + best[9] >= best[n]))) {
            if (d + best[9] <= best[n]) {
                return;
            }
            s = 8;
        }
    } else if (x == 7) {
        if (!((a[8] == 8 || (a[8] == -1 && !(f & 128))) && (a[8] == -1 || d + best[8] >= best[n]))) {
            if (d + best[8] <= best[n]) {
                return;
            }
            s = 7;
        }
    } else if (x == 8) {
        if (!((a[7] == 7 || (a[7] == -1 && !(f & 256))) && (a[7] == -1 || d + best[7] >= best[n]))) {
            if (d + best[7] <= best[n]) {
                return;
            }
            s = 6;
        }
    } else if (x == 9) {
        if (!((a[6] == 6 || (a[6] == -1 && !(f & 512))) && (a[6] == -1 || d + best[6] >= best[n]))) {
            if (d + best[6] <= best[n]) {
                return;
            }
            s = 5;
        }
    } else if (x == 10) {
        if (!((a[5] == 5 || (a[5] == -1 && !(f & 1024))) && (a[5] == -1 || d + best[5] >= best[n]))) {
            if (d + best[5] <= best[n]) {
                return;
            }
            s = 4;
        }
    } else if (x == 11) {
        if (!((a[4] == 4 || (a[4] == -1 && !(f & 2048))) && (a[4] == -1 || d + best[4] >= best[n]))) {
            if (d + best[4] <= best[n]) {
                return;
            }
            s = 3;
        }
    } else if (x == 12) {
        if (!((a[3] == 3 || (a[3] == -1 && !(f & 4096))) && (a[3] == -1 || d + best[3] >= best[n]))) {
            if (d + best[3] <= best[n]) {
                return;
            }
            s = 2;
        }
    } else if (x == 13) {
        if (!((a[2] == 2 || (a[2] == -1 && !(f & 8192))) && (a[2] == -1 || d + best[2] >= best[n]))) {
            if (d + best[2] <= best[n]) {
                return;
            }
            s = 1;
        }
    } else if (x == 14) {
        if (!((a[1] == 1 || (a[1] == -1 && !(f & 16384))) && (a[1] == -1 || d + best[1] >= best[n]))) {
            if (d + best[1] <= best[n]) {
                return;
            }
            s = 0;
        }
    } else {
        return;
    }
    
    for (x = 1; x <= 15; x = x + 1) {
        if (a[x] == x || ((a[x] == -1) && !(f & (1 << x)))) {
            b[0] = x;
            for (j = x; j > 0; j = j - 1) {
                b[x - (j - 1)] = a[j - 1];
            }
            tryswaps(b, f | (1 << x), s, d + 1, best, n);
        }
        if (s == x) {
            return;
        }
    }
    return;
}
