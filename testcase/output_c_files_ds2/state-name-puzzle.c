void find_mix(int n_states, const char* states[5]) {
    int i;
    int j;
    int n;
    int k;
    int c;
    int l[5][26];
    const char* name[5][2];
    int p[5];
    int a[5];
    int b[5];
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 26; j = j + 1) {
            l[i][j] = 0;
        }
        name[i][0] = 0;
        name[i][1] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        p[i] = 0;
    }
    
    n = n_states * (n_states - 1) / 2;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (!name[p[0]][0]) {
                name[p[0]][0] = states[i];
            } else {
                name[p[0]][1] = states[i];
            }
            c = states[i][0];
            while (c) {
                if (c >= 97 && c <= 122) {
                    l[p[0]][c - 97] = l[p[0]][c - 97] + 1;
                }
                if (c >= 65 && c <= 90) {
                    l[p[0]][c - 65] = l[p[0]][c - 65] + 1;
                }
                c = states[i][0];
            }
            
            if (!name[p[0]][0]) {
                name[p[0]][0] = states[j];
            } else {
                name[p[0]][1] = states[j];
            }
            c = states[j][0];
            while (c) {
                if (c >= 97 && c <= 122) {
                    l[p[0]][c - 97] = l[p[0]][c - 97] + 1;
                }
                if (c >= 65 && c <= 90) {
                    l[p[0]][c - 65] = l[p[0]][c - 65] + 1;
                }
                c = states[j][0];
            }
            p[0] = p[0] + 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            for (k = 0; k < 26; k = k + 1) {
                if (l[i][k] > l[j][k]) {
                    a[0] = 1;
                    break;
                } else if (l[i][k] < l[j][k]) {
                    a[0] = -1;
                    break;
                } else {
                    a[0] = 0;
                }
            }
            if (a[0] == 0) {
                if (name[i][0] != name[j][0] && name[i][1] != name[j][0] && name[i][1] != name[j][1]) {
                }
            }
        }
    }
    return;
}
