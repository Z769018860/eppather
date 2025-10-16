int create_huffman_codes(int freqs[256], int codes[256][2]) {
    int efreqs[512];
    int preds[512];
    int heap_h[512];
    int heap_n = 0;
    int heap_s = 512;
    int extf = 256;
    int i;
    int r1;
    int r2;
    int ix;
    int bc;
    int bn;

    for (i = 0; i < 256; i = i + 1) {
        efreqs[i] = freqs[i];
    }
    for (i = 256; i < 512; i = i + 1) {
        efreqs[i] = 0;
    }

    for (i = 0; i < 256; i = i + 1) {
        if (efreqs[i] > 0) {
            heap_h[heap_n] = i;
            heap_n = heap_n + 1;
        }
    }

    for (i = 0; i < heap_n; i = i + 1) {
        for (int j = i + 1; j < heap_n; j = j + 1) {
            if (efreqs[heap_h[i]] < efreqs[heap_h[j]]) {
                int t = heap_h[i];
                heap_h[i] = heap_h[j];
                heap_h[j] = t;
            }
        }
    }

    while (heap_n > 1) {
        r1 = heap_h[heap_n - 1];
        heap_n = heap_n - 1;
        r2 = heap_h[heap_n - 1];
        heap_n = heap_n - 1;
        efreqs[extf] = efreqs[r1] + efreqs[r2];
        heap_h[heap_n] = extf;
        heap_n = heap_n + 1;
        preds[r1] = extf;
        preds[r2] = -extf;
        extf = extf + 1;

        for (i = 0; i < heap_n; i = i + 1) {
            for (int j = i + 1; j < heap_n; j = j + 1) {
                if (efreqs[heap_h[i]] < efreqs[heap_h[j]]) {
                    int t = heap_h[i];
                    heap_h[i] = heap_h[j];
                    heap_h[j] = t;
                }
            }
        }
    }

    r1 = heap_h[heap_n - 1];
    heap_n = heap_n - 1;
    preds[r1] = r1;

    for (i = 0; i < 256; i = i + 1) {
        if (efreqs[i] == 0) {
            codes[i][0] = 0;
            codes[i][1] = 0;
            continue;
        }
        bc = 0;
        bn = 0;
        ix = i;
        while (preds[ix] != ix && preds[ix] != -ix) {
            if (preds[ix] >= 0) {
                bc = bc | (1 << bn);
            }
            ix = (preds[ix] >= 0) ? preds[ix] : -preds[ix];
            bn = bn + 1;
        }
        codes[i][0] = bn;
        codes[i][1] = bc;
    }
    return;
}
