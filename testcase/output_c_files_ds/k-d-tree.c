int dist(int a[3], int b[3], int dim) {
    int t;
    int d = 0;
    for (int i = 0; i < dim; i = i + 1) {
        t = a[i] - b[i];
        d = d + t * t;
    }
    return d;
}

void swap(int x[3], int y[3]) {
    int tmp[3];
    for (int i = 0; i < 3; i = i + 1) {
        tmp[i] = x[i];
    }
    for (int i = 0; i < 3; i = i + 1) {
        x[i] = y[i];
    }
    for (int i = 0; i < 3; i = i + 1) {
        y[i] = tmp[i];
    }
}

int find_median(int start[100][3], int end, int idx) {
    if (end <= 0) {
        return -1;
    }
    if (end == 1) {
        return 0;
    }

    int md = end / 2;
    int pivot;
    int store;
    int p;
    while (1) {
        pivot = start[md][idx];

        swap(start[md], start[end - 1]);
        store = 0;
        for (p = 0; p < end; p = p + 1) {
            if (start[p][idx] < pivot) {
                if (p != store) {
                    swap(start[p], start[store]);
                }
                store = store + 1;
            }
        }
        swap(start[store], start[end - 1]);

        if (start[store][idx] == start[md][idx]) {
            return md;
        }

        if (store > md) {
            end = store;
        } else {
            start = start + store;
            end = end - store;
        }
    }
    return -1;
}

void nearest(int tree[100][3], int nd[3], int i, int dim, int best[3], int* best_dist, int* visited) {
    int d;
    int dx;
    int dx2;

    if (tree[0][0] == 0 && tree[0][1] == 0 && tree[0][2] == 0) {
        return;
    }
    d = dist(tree[0], nd, dim);
    dx = tree[0][i] - nd[i];
    dx2 = dx * dx;

    *visited = *visited + 1;

    if (*best_dist == -1 || d < *best_dist) {
        *best_dist = d;
        for (int j = 0; j < 3; j = j + 1) {
            best[j] = tree[0][j];
        }
    }

    if (*best_dist == 0) {
        return;
    }

    i = i + 1;
    if (i >= dim) {
        i = 0;
    }

    if (dx > 0) {
        nearest(tree + 1, nd, i, dim, best, best_dist, visited);
    } else {
        nearest(tree + 2, nd, i, dim, best, best_dist, visited);
    }
    if (dx2 >= *best_dist) {
        return;
    }
    if (dx > 0) {
        nearest(tree + 2, nd, i, dim, best, best_dist, visited);
    } else {
        nearest(tree + 1, nd, i, dim, best, best_dist, visited);
    }
    return;
}
