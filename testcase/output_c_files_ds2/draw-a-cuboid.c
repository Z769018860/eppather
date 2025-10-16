void face_hit(int face_v0_0, int face_v0_1, int face_v0_2, int face_v2_0, int face_v2_1, int face_v2_2, int face_norm_0, int face_norm_1, int face_norm_2, int src_0, int src_1, int src_2, int dir_0, int dir_1, int dir_2, int hit[3], int d[1]) {
    int dist;
    int i;
    for (i = 0; i < 3; i = i + 1) {
        if (face_norm_0 || face_norm_1 || face_norm_2) {
            if (face_norm_0) {
                dist = (face_v0_0 - src_0) / dir_0;
            }
            if (face_norm_1) {
                dist = (face_v0_1 - src_1) / dir_1;
            }
            if (face_norm_2) {
                dist = (face_v0_2 - src_2) / dir_2;
            }
        }
    }

    hit[0] = src_0 + dir_0 * dist;
    hit[1] = src_1 + dir_1 * dist;
    hit[2] = src_2 + dir_2 * dist;

    int dot_val = dir_0 * face_norm_0 + dir_1 * face_norm_1 + dir_2 * face_norm_2;
    if (dot_val < 0) {
        dot_val = -dot_val;
    }
    d[0] = dot_val * dist;

    int in_range_0;
    int in_range_1;
    if (face_norm_0) {
        in_range_0 = (hit[1] - face_v0_1) * (hit[1] - face_v2_1) <= 0;
        in_range_1 = (hit[2] - face_v0_2) * (hit[2] - face_v2_2) <= 0;
        d[0] = in_range_0 && in_range_1;
    } else if (face_norm_1) {
        in_range_0 = (hit[0] - face_v0_0) * (hit[0] - face_v2_0) <= 0;
        in_range_1 = (hit[2] - face_v0_2) * (hit[2] - face_v2_2) <= 0;
        d[0] = in_range_0 && in_range_1;
    } else if (face_norm_2) {
        in_range_0 = (hit[0] - face_v0_0) * (hit[0] - face_v2_0) <= 0;
        in_range_1 = (hit[1] - face_v0_1) * (hit[1] - face_v2_1) <= 0;
        d[0] = in_range_0 && in_range_1;
    } else {
        d[0] = 0;
    }
    return;
}
