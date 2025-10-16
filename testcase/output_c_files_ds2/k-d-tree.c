void nearest(int root_x[3], int root_left[3], int root_right[3], int nd_x[3], int i, int dim, int best_x[3], int best_dist[1]) {
    int d[1];
    int dx[1];
    int dx2[1];
    int tmp[1];
    int j;
    
    if (root_x[0] == 0 && root_x[1] == 0 && root_x[2] == 0) {
        return;
    }
    
    d[0] = 0;
    for (j = 0; j < dim; j = j + 1) {
        tmp[0] = root_x[j] - nd_x[j];
        d[0] = d[0] + tmp[0] * tmp[0];
    }
    
    dx[0] = root_x[i] - nd_x[i];
    dx2[0] = dx[0] * dx[0];
    
    if (best_x[0] == 0 && best_x[1] == 0 && best_x[2] == 0 || d[0] < best_dist[0]) {
        best_dist[0] = d[0];
        for (j = 0; j < dim; j = j + 1) {
            best_x[j] = root_x[j];
        }
    }
    
    if (best_dist[0] == 0) {
        return;
    }
    
    i = i + 1;
    if (i >= dim) {
        i = 0;
    }
    
    if (dx[0] > 0) {
        nearest(root_left, root_left, root_right, nd_x, i, dim, best_x, best_dist);
    } else {
        nearest(root_right, root_left, root_right, nd_x, i, dim, best_x, best_dist);
    }
    
    if (dx2[0] >= best_dist[0]) {
        return;
    }
    
    if (dx[0] > 0) {
        nearest(root_right, root_left, root_right, nd_x, i, dim, best_x, best_dist);
    } else {
        nearest(root_left, root_left, root_right, nd_x, i, dim, best_x, best_dist);
    }
    
    return;
}
