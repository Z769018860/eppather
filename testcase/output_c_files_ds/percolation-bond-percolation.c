int fill(int cells[], int m, int n, int end, int p) {
    if ((cells[p] & 1)) {
        return 0;
    }
    cells[p] = cells[p] | 1;
    if (p >= end) {
        return 1;
    }
    if (!(cells[p] & 4) && fill(cells, m, n, end, p + m)) {
        return 1;
    }
    if (!(cells[p] & 2) && fill(cells, m, n, end, p + 1)) {
        return 1;
    }
    if (!(cells[p - 1] & 2) && fill(cells, m, n, end, p - 1)) {
        return 1;
    }
    if (!(cells[p - m] & 4) && fill(cells, m, n, end, p - m)) {
        return 1;
    }
    return 0;
}

int percolate(int cells[], int m, int n, int end) {
    int i;
    for (i = 0; i < m; i = i + 1) {
        if (fill(cells, m, n, end, i)) {
            return 1;
        }
    }
    return 0;
}

void make_grid(int cells[], int start[], int m, int n, int thresh) {
    int i;
    int j;
    int end;
    for (i = 0; i < m; i = i + 1) {
        start[i] = 4 | 2;
    }
    end = 0;
    for (i = 0; i < n; i = i + 1) {
        for (j = m - 1; j > 0; j = j - 1) {
            cells[end] = ((rand() < thresh ? 4 : 0) | (rand() < thresh ? 2 : 0));
            end = end + 1;
        }
        cells[end] = 2 | (rand() < thresh ? 4 : 0);
        end = end + 1;
    }
    for (i = 0; i < m; i = i + 1) {
        cells[end + i] = 0;
    }
    return;
}
