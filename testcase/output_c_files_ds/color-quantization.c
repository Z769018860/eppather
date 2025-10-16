int cmp_node(int* a, int* b) {
    if (a[3] < b[3]) {
        return -1;
    }
    if (a[3] > b[3]) {
        return 1;
    }
    int ac = (a[4] * (1 + a[6])) >> a[7];
    int bc = (b[4] * (1 + b[6])) >> b[7];
    if (ac < bc) {
        return -1;
    }
    if (ac > bc) {
        return 1;
    }
    return 0;
}

void node_insert(int* root, int* pix, int* kids[8], int* parent) {
    int bit = 128;
    int depth = 0;
    for (depth = 0; depth < 8; depth = depth + 1) {
        int i = 0;
        if (pix[1] & bit) {
            i = i + 4;
        }
        if (pix[0] & bit) {
            i = i + 2;
        }
        if (pix[2] & bit) {
            i = i + 1;
        }
        if (kids[i] == 0) {
            kids[i] = parent;
        }
        root = kids[i];
        bit = bit >> 1;
    }
    root[0] = root[0] + pix[0];
    root[1] = root[1] + pix[1];
    root[2] = root[2] + pix[2];
    root[4] = root[4] + 1;
    return;
}

void node_fold(int* p, int* q) {
    if (p[3] != 0) {
        return;
    }
    q[4] = q[4] + p[4];
    q[0] = q[0] + p[0];
    q[1] = q[1] + p[1];
    q[2] = q[2] + p[2];
    q[3] = q[3] - 1;
    q[5 + p[6]] = 0;
    return;
}

void color_replace(int* root, int* pix, int* kids[8]) {
    int bit = 128;
    int i = 0;
    for (bit = 128; bit != 0; bit = bit >> 1) {
        i = 0;
        if (pix[1] & bit) {
            i = i + 4;
        }
        if (pix[0] & bit) {
            i = i + 2;
        }
        if (pix[2] & bit) {
            i = i + 1;
        }
        if (kids[i] == 0) {
            break;
        }
        root = kids[i];
    }
    pix[0] = root[0];
    pix[1] = root[1];
    pix[2] = root[2];
    return;
}

void color_quant(int* im, int n_colors, int w, int h, int* pix) {
    int heap_buf[256][8];
    int heap_n = 0;
    int root[8] = {0};
    int kids[8] = {0};
    int parent[8] = {0};
    int i = 0;
    for (i = 0; i < w * h; i = i + 1) {
        node_insert(root, pix + i * 3, kids, parent);
    }
    while (heap_n > n_colors + 1) {
        node_fold(heap_buf[heap_n - 1], parent);
        heap_n = heap_n - 1;
    }
    for (i = 0; i < w * h; i = i + 1) {
        color_replace(root, pix + i * 3, kids);
    }
    return;
}
