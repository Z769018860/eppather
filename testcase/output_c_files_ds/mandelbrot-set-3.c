void rewritten_function() {
    int k;
    int i;
    int j;
    int r;
    int x;
    int y = -16;
    char chars[] = " .:-;!/>)|&IH%*#";
    
    for (; y < 15; y = y + 1) {
        for (x = 0; x < 84; x = x + 1) {
            k = 0;
            r = 0;
            i = 0;
            for (; k < 111; k = k + 1) {
                j = r * r - i * i - 2 + x / 25;
                i = 2 * r * i + y / 10;
                if (j * j + i * i >= 11) {
                    break;
                }
                r = j;
            }
        }
    }
    return;
}
