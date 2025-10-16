void create_huffman_codes(int freqs[256], int codes_nbits[256], int codes_code[256]) {
    int heap_h[512];
    int heap_n = 0;
    int heap_s = 512;
    long efreqs[512];
    int preds[512];
    int extf = 256;
    int r1;
    int r2;
    int i;
    int j;
    int k;
    int a[512];
    int t_;
    int bc;
    int bn;
    int ix;

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

    for (i = 1; i < heap_n; i = i + 1) {
        j = i;
        while (j > 0) {
            if (efreqs[heap_h[j - 1]] >= efreqs[heap_h[j]]) {
                t_ = heap_h[j - 1];
                heap_h[j - 1] = heap_h[j];
                heap_h[j] = t_;
                j = j - 1;
            } else {
                break;
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

        for (i = 1; i < heap_n; i = i + 1) {
            j = i;
            while (j > 0) {
                if (efreqs[heap_h[j - 1]] >= efreqs[heap_h[j]]) {
                    t_ = heap_h[j - 1];
                    heap_h[j - 1] = heap_h[j];
                    heap_h[j] = t_;
                    j = j - 1;
                } else {
                    break;
                }
            }
        }
    }

    r1 = heap_h[heap_n - 1];
    heap_n = heap_n - 1;
    preds[r1] = r1;

    for (i = 0; i < 256; i = i + 1) {
        bc = 0;
        bn = 0;
        if (efreqs[i] == 0) {
            codes_nbits[i] = 0;
            codes_code[i] = 0;
            continue;
        }
        ix = i;
        while (preds[ix] != ix && preds[ix] != -ix) {
            if (preds[ix] >= 0) {
                bc = bc | (1 << bn);
            }
            ix = preds[ix];
            if (ix < 0) {
                ix = -ix;
            }
            bn = bn + 1;
        }
        codes_nbits[i] = bn;
        codes_code[i] = bc;
    }
    return;
}
