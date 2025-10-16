void face_hit_combined(double src[3], double dir[3], double hit[3], double *d, int *result) {
    double v000[3] = { -4, -3, -2 };
    double v100[3] = {  4, -3, -2 };
    double v010[3] = { -4,  3, -2 };
    double v110[3] = {  4,  3, -2 };
    double v001[3] = { -4, -3,  2 };
    double v101[3] = {  4, -3,  2 };
    double v011[3] = { -4,  3,  2 };
    double v111[3] = {  4,  3,  2 };
    
    double face_norms[6][3] = {
        {  0,  0, -1 },
        {  0,  0,  1 },
        { -1,  0,  0 },
        {  1,  0,  0 },
        {  0, -1,  0 },
        {  0,  1,  0 }
    };
    
    double *face_verts[6][4] = {
        { v000, v010, v110, v100 },
        { v001, v011, v111, v101 },
        { v000, v010, v011, v001 },
        { v100, v110, v111, v101 },
        { v000, v100, v101, v001 },
        { v010, v110, v111, v011 }
    };
    
    int i;
    double dist;
    int face_index;
    double temp;
    double dot_product;
    double x_diff;
    double y_diff;
    double z_diff;
    
    for (face_index = 0; face_index < 6; face_index = face_index + 1) {
        for (i = 0; i < 3; i = i + 1) {
            if (face_norms[face_index][i] != 0) {
                dist = (face_verts[face_index][0][i] - src[i]) / dir[i];
            }
        }
        
        hit[0] = src[0] + dir[0] * dist;
        hit[1] = src[1] + dir[1] * dist;
        hit[2] = src[2] + dir[2] * dist;
        
        dot_product = dir[0] * face_norms[face_index][0] + dir[1] * face_norms[face_index][1] + dir[2] * face_norms[face_index][2];
        if (dot_product < 0) {
            dot_product = -dot_product;
        }
        *d = dot_product * dist;
        
        if (face_norms[face_index][0] != 0) {
            x_diff = (hit[1] - face_verts[face_index][0][1]) * (hit[1] - face_verts[face_index][2][1]);
            y_diff = (hit[2] - face_verts[face_index][0][2]) * (hit[2] - face_verts[face_index][2][2]);
            if (x_diff <= 0 && y_diff <= 0) {
                *result = 1;
                return;
            }
        } else if (face_norms[face_index][1] != 0) {
            x_diff = (hit[0] - face_verts[face_index][0][0]) * (hit[0] - face_verts[face_index][2][0]);
            y_diff = (hit[2] - face_verts[face_index][0][2]) * (hit[2] - face_verts[face_index][2][2]);
            if (x_diff <= 0 && y_diff <= 0) {
                *result = 1;
                return;
            }
        } else if (face_norms[face_index][2] != 0) {
            x_diff = (hit[0] - face_verts[face_index][0][0]) * (hit[0] - face_verts[face_index][2][0]);
            y_diff = (hit[1] - face_verts[face_index][0][1]) * (hit[1] - face_verts[face_index][2][1]);
            if (x_diff <= 0 && y_diff <= 0) {
                *result = 1;
                return;
            }
        }
    }
    *result = 0;
    return;
}
