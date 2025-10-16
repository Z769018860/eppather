void translate(int dit, const char i[5], char o[100000]) {
    const char* ascii = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?'!/()&:;=+-_\"$@";
    const char* itu[54] = {
        "13","3111","3131","311","1","1131","331","1111","11","1333","313","1311","33","31","333","1331","3313","131","111","3","113","1113","133","3113","3133","3311","33333","13333","11333","11133","11113","11111","31111","33111","33311","33331","131313","331133","113311","133331","313133","31131","31331","313313","13111","333111","313131","31113","13131","311113","113313","131131","1113113","133131"
    };
    char dih[50];
    char dah[50];
    char medium[30];
    char word[30];
    const char* dd[2] = {dih, dah};
    int n;
    int m;
    int k;
    int p;
    int q;
    int r;
    int s;
    int t;
    int u;
    int v;
    int w;
    int x;
    int y;
    int z;
    
    for (n = 0; n < 50; n = n + 1) {
        dih[n] = 0;
        dah[n] = 0;
    }
    for (m = 0; m < 30; m = m + 1) {
        medium[m] = 0;
        word[m] = 0;
    }
    
    for (p = 0; p < 100000; p = p + 1) {
        o[p] = 0;
    }
    
    o[0] = 'b';
    o[1] = 'e';
    o[2] = 'e';
    o[3] = 'p';
    o[4] = 0;
    
    for (q = 0; q < 50; q = q + 1) {
        if (q < 25) {
            dih[q] = ' ';
            dah[q] = ' ';
        }
    }
    
    for (r = 0; r < 30; r = r + 1) {
        if (r < 15) {
            medium[r] = ' ';
            word[r] = ' ';
        }
    }
    
    for (s = 0; s < 5; s = s + 1) {
        if (i[s] == 0) {
            break;
        }
        const char* pc = 0;
        for (t = 0; t < 54; t = t + 1) {
            if (ascii[t] == (i[s] >= 'a' && i[s] <= 'z' ? i[s] - 32 : i[s])) {
                pc = itu[t];
                break;
            }
        }
        if (pc == 0) {
            for (u = 0; word[u] != 0; u = u + 1) {
                o[strlen(o)] = word[u];
            }
        } else {
            for (v = 0; pc[v] != 0; v = v + 1) {
                const char* morse = pc[v] == '3' ? dah : dih;
                for (w = 0; morse[w] != 0; w = w + 1) {
                    o[strlen(o)] = morse[w];
                }
            }
            for (x = 0; medium[x] != 0; x = x + 1) {
                o[strlen(o)] = medium[x];
            }
        }
    }
    for (y = 0; word[y] != 0; y = y + 1) {
        o[strlen(o)] = word[y];
    }
    return;
}
