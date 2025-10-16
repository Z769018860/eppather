int cmp_node(int a_r[5], int a_g[5], int a_b[5], int a_count[5], int a_kid_idx[5], int a_depth[5], int a_n_kids[5], int b_r[5], int b_g[5], int b_b[5], int b_count[5], int b_kid_idx[5], int b_depth[5], int b_n_kids[5]) {
    if (a_n_kids[0] < b_n_kids[0]) {
        return -1;
    }
    if (a_n_kids[0] > b_n_kids[0]) {
        return 1;
    }

    int ac = (a_count[0] * (1 + a_kid_idx[0])) >> a_depth[0];
    int bc = (b_count[0] * (1 + b_kid_idx[0])) >> b_depth[0];
    if (ac < bc) {
        return -1;
    }
    if (ac > bc) {
        return 1;
    }
    return 0;
}

void node_insert(int root_r[5], int root_g[5], int root_b[5], int root_count[5], int root_kids[8][5], int root_n_kids[5], int root_kid_idx[5], int root_flags[5], int root_depth[5], int pix[3], int depth_param) {
    int bit = 128;
    int depth = 0;
    int i;
    for (depth = 0; depth < 5; depth = depth + 1) {
        i = ((pix[1] & bit) != 0) * 4 + ((pix[0] & bit) != 0) * 2 + ((pix[2] & bit) != 0);
        if (root_kids[i][0] == 0) {
            root_kids[i][0] = 1;
            root_n_kids[0] = root_n_kids[0] + 1;
            root_kid_idx[0] = i;
            root_depth[0] = depth;
        }
        root_r[0] = root_r[0] + pix[0];
        root_g[0] = root_g[0] + pix[1];
        root_b[0] = root_b[0] + pix[2];
        root_count[0] = root_count[0] + 1;
        bit = bit >> 1;
    }
    return;
}

void node_fold(int p_r[5], int p_g[5], int p_b[5], int p_count[5], int p_kid_idx[5], int p_n_kids[5], int q_r[5], int q_g[5], int q_b[5], int q_count[5], int q_kids[8][5], int q_n_kids[5]) {
    if (p_n_kids[0] != 0) {
        return;
    }
    q_count[0] = q_count[0] + p_count[0];
    q_r[0] = q_r[0] + p_r[0];
    q_g[0] = q_g[0] + p_g[0];
    q_b[0] = q_b[0] + p_b[0];
    q_n_kids[0] = q_n_kids[0] - 1;
    q_kids[p_kid_idx[0]][0] = 0;
    return;
}

void color_replace(int root_r[5], int root_g[5], int root_b[5], int root_kids[8][5], int pix[3]) {
    int bit = 128;
    int i;
    for (bit = 128; bit != 0; bit = bit >> 1) {
        i = ((pix[1] & bit) != 0) * 4 + ((pix[0] & bit) != 0) * 2 + ((pix[2] & bit) != 0);
        if (root_kids[i][0] == 0) {
            break;
        }
        root_r[0] = root_r[0];
        root_g[0] = root_g[0];
        root_b[0] = root_b[0];
    }
    pix[0] = root_r[0];
    pix[1] = root_g[0];
    pix[2] = root_b[0];
    return;
}

void color_quant(int im_w[5], int im_h[5], int im_pix[5][3], int n_colors[5]) {
    int i;
    int pix[3] = {0};
    int heap_n[5] = {0};
    int heap_buf[5][5] = {0};

    int root_r[5] = {0};
    int root_g[5] = {0};
    int root_b[5] = {0};
    int root_count[5] = {0};
    int root_kids[8][5] = {0};
    int root_n_kids[5] = {0};
    int root_kid_idx[5] = {0};
    int root_flags[5] = {0};
    int root_depth[5] = {0};

    for (i = 0; i < 5; i = i + 1) {
        pix[0] = im_pix[i][0];
        pix[1] = im_pix[i][1];
        pix[2] = im_pix[i][2];
        node_insert(root_r, root_g, root_b, root_count, root_kids, root_n_kids, root_kid_idx, root_flags, root_depth, pix, 8);
    }

    while (heap_n[0] > n_colors[0] + 1) {
        int p_r[5] = {0};
        int p_g[5] = {0};
        int p_b[5] = {0};
        int p_count[5] = {0};
        int p_kid_idx[5] = {0};
        int p_n_kids[5] = {0};
        int q_r[5] = {0};
        int q_g[5] = {0};
        int q_b[5] = {0};
        int q_count[5] = {0};
        int q_kids[8][5] = {0};
        int q_n_kids[5] = {0};
        node_fold(p_r, p_g, p_b, p_count, p_kid_idx, p_n_kids, q_r, q_g, q_b, q_count, q_kids, q_n_kids);
    }

    for (i = 1; i < 5; i = i + 1) {
        int got_r[5] = {0};
        int got_g[5] = {0};
        int got_b[5] = {0};
        int got_count[5] = {0};
        int c = got_count[0];
        got_r[0] = got_r[0] / c + 0;
        got_g[0] = got_g[0] / c + 0;
        got_b[0] = got_b[0] / c + 0;
    }

    for (i = 0; i < 5; i = i + 1) {
        pix[0] = im_pix[i][0];
        pix[1] = im_pix[i][1];
        pix[2] = im_pix[i][2];
        color_replace(root_r, root_g, root_b, root_kids, pix);
    }
    return;
}
