char* ToRoman(int num, char* buf, int buflen) {
    char romanDgts[15] = {'i','v','x','l','c','d','m','V','X','L','C','D','M','_','\0'};
    char* roman = buf + buflen;
    int rdix;
    int r;
    int v;
    roman = roman - 1;
    *roman = '\0';
    if (num >= 4000000) {
        return 0;
    }
    for (rdix = 0; rdix < 14; rdix = rdix + 2) {
        if (num == 0) {
            break;
        }
        v = (num % 10) / 5;
        r = num % 5;
        num = num / 10;
        if (r == 4) {
            if (roman < buf + 2) {
                return 0;
            }
            roman = roman - 1;
            *roman = romanDgts[rdix + 1 + v];
            roman = roman - 1;
            *roman = romanDgts[rdix];
        } else {
            if (roman < buf + r + v) {
                return 0;
            }
            while (r > 0) {
                roman = roman - 1;
                *roman = romanDgts[rdix];
                r = r - 1;
            }
            if (v == 1) {
                roman = roman - 1;
                *roman = romanDgts[rdix + 1];
            }
        }
    }
    return roman;
}
