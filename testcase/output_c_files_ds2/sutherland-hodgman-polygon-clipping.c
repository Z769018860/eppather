int left_of(int a_x[5], int a_y[5], int b_x[5], int b_y[5], int c_x[5], int c_y[5])
{
    int tmp1_x[5];
    int tmp1_y[5];
    int tmp2_x[5];
    int tmp2_y[5];
    tmp1_x[0] = b_x[0] - a_x[0];
    tmp1_y[0] = b_y[0] - a_y[0];
    tmp2_x[0] = c_x[0] - b_x[0];
    tmp2_y[0] = c_y[0] - b_y[0];
    int x[5];
    x[0] = tmp1_x[0] * tmp2_y[0] - tmp1_y[0] * tmp2_x[0];
    if (x[0] < 0)
    {
        return -1;
    }
    else
    {
        if (x[0] > 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int line_sect(int x0_x[5], int x0_y[5], int x1_x[5], int x1_y[5], int y0_x[5], int y0_y[5], int y1_x[5], int y1_y[5], int res_x[5], int res_y[5])
{
    int dx_x[5];
    int dx_y[5];
    int dy_x[5];
    int dy_y[5];
    int d_x[5];
    int d_y[5];
    dx_x[0] = x1_x[0] - x0_x[0];
    dx_y[0] = x1_y[0] - x0_y[0];
    dy_x[0] = y1_x[0] - y0_x[0];
    dy_y[0] = y1_y[0] - y0_y[0];
    d_x[0] = x0_x[0] - y0_x[0];
    d_y[0] = x0_y[0] - y0_y[0];
    int dyx[5];
    dyx[0] = dy_x[0] * dx_y[0] - dy_y[0] * dx_x[0];
    if (dyx[0] == 0)
    {
        return 0;
    }
    dyx[0] = (d_x[0] * dx_y[0] - d_y[0] * dx_x[0]) / dyx[0];
    if (dyx[0] <= 0 || dyx[0] >= 1)
    {
        return 0;
    }
    res_x[0] = y0_x[0] + dyx[0] * dy_x[0];
    res_y[0] = y0_y[0] + dyx[0] * dy_y[0];
    return 1;
}

void poly_edge_clip(int sub_x[5][5], int sub_y[5][5], int sub_len[5], int x0_x[5], int x0_y[5], int x1_x[5], int x1_y[5], int left[5], int res_x[5][5], int res_y[5][5], int res_len[5])
{
    int side0[5];
    int side1[5];
    int tmp_x[5];
    int tmp_y[5];
    int v0_x[5];
    int v0_y[5];
    int v1_x[5];
    int v1_y[5];
    v0_x[0] = sub_x[sub_len[0] - 1][0];
    v0_y[0] = sub_y[sub_len[0] - 1][0];
    res_len[0] = 0;
    side0[0] = left_of(x0_x, x0_y, x1_x, x1_y, v0_x, v0_y);
    if (side0[0] != -left[0])
    {
        res_x[res_len[0]][0] = v0_x[0];
        res_y[res_len[0]][0] = v0_y[0];
        res_len[0] = res_len[0] + 1;
    }
    for (int i = 0; i < sub_len[0]; i = i + 1)
    {
        v1_x[0] = sub_x[i][0];
        v1_y[0] = sub_y[i][0];
        side1[0] = left_of(x0_x, x0_y, x1_x, x1_y, v1_x, v1_y);
        if (side0[0] + side1[0] == 0 && side0[0])
        {
            if (line_sect(x0_x, x0_y, x1_x, x1_y, v0_x, v0_y, v1_x, v1_y, tmp_x, tmp_y))
            {
                res_x[res_len[0]][0] = tmp_x[0];
                res_y[res_len[0]][0] = tmp_y[0];
                res_len[0] = res_len[0] + 1;
            }
        }
        if (i == sub_len[0] - 1)
        {
            break;
        }
        if (side1[0] != -left[0])
        {
            res_x[res_len[0]][0] = v1_x[0];
            res_y[res_len[0]][0] = v1_y[0];
            res_len[0] = res_len[0] + 1;
        }
        v0_x[0] = v1_x[0];
        v0_y[0] = v1_y[0];
        side0[0] = side1[0];
    }
    return;
}

void poly_clip(int sub_x[5][5], int sub_y[5][5], int sub_len[5], int clip_x[5][5], int clip_y[5][5], int clip_len[5], int res_x[5][5], int res_y[5][5], int res_len[5])
{
    int p1_x[5][5];
    int p1_y[5][5];
    int p1_len[5];
    int p2_x[5][5];
    int p2_y[5][5];
    int p2_len[5];
    int dir[5];
    dir[0] = left_of(clip_x[0], clip_y[0], clip_x[1], clip_y[1], clip_x[2], clip_y[2]);
    poly_edge_clip(sub_x, sub_y, sub_len, clip_x[clip_len[0] - 1], clip_y[clip_len[0] - 1], clip_x[0], clip_y[0], dir, p2_x, p2_y, p2_len);
    for (int i = 0; i < clip_len[0] - 1; i = i + 1)
    {
        for (int j = 0; j < 5; j = j + 1)
        {
            for (int k = 0; k < 5; k = k + 1)
            {
                int temp_x = p2_x[j][k];
                p2_x[j][k] = p1_x[j][k];
                p1_x[j][k] = temp_x;
                int temp_y = p2_y[j][k];
                p2_y[j][k] = p1_y[j][k];
                p1_y[j][k] = temp_y;
            }
        }
        int temp_len = p2_len[0];
        p2_len[0] = p1_len[0];
        p1_len[0] = temp_len;
        if (p1_len[0] == 0)
        {
            p2_len[0] = 0;
            break;
        }
        poly_edge_clip(p1_x, p1_y, p1_len, clip_x[i], clip_y[i], clip_x[i + 1], clip_y[i + 1], dir, p2_x, p2_y, p2_len);
    }
    for (int i = 0; i < p2_len[0]; i = i + 1)
    {
        res_x[i][0] = p2_x[i][0];
        res_y[i][0] = p2_y[i][0];
    }
    res_len[0] = p2_len[0];
    return;
}
