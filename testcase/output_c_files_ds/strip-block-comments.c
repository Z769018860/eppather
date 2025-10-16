char* stripcomments(char* s) {
    char ca[3] = {'/', '*', '\0'};
    char cb[3] = {'*', '/', '\0'};
    int al = 2;
    int bl = 2;
    int len = 0;
    char* a;
    char* b;
    int i;
    int j;
    int k;

    for (i = 0; s[i] != '\0'; i = i + 1) {
        len = len + 1;
    }
    len = len + 1;

    for (;;) {
        a = 0;
        for (i = 0; i < len - al; i = i + 1) {
            if (s[i] == ca[0]) {
                int match = 1;
                for (j = 1; j < al; j = j + 1) {
                    if (s[i + j] != ca[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    a = s + i;
                    break;
                }
            }
        }
        if (a == 0) {
            break;
        }

        b = 0;
        for (i = (a - s) + al; i < len - bl; i = i + 1) {
            if (s[i] == cb[0]) {
                int match = 1;
                for (j = 1; j < bl; j = j + 1) {
                    if (s[i + j] != cb[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    b = s + i + bl;
                    break;
                }
            }
        }
        if (b == 0) {
            break;
        }

        for (k = 0; k < len - (b - a); k = k + 1) {
            a[k] = b[k];
        }
        len = len - (b - a);
    }

    return s;
}
