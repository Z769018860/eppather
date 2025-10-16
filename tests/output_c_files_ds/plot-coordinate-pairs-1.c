void minmax(int x[10], int y[10], int* minx, int* maxx, int* miny, int* maxy) {
    *minx = x[0];
    *maxx = x[0];
    *miny = y[0];
    *maxy = y[0];
    for(int i = 1; i < 10; i = i + 1) {
        if (x[i] < *minx) {
            *minx = x[i];
        }
        if (x[i] > *maxx) {
            *maxx = x[i];
        }
        if (y[i] < *miny) {
            *miny = y[i];
        }
        if (y[i] > *maxy) {
            *maxy = y[i];
        }
    }
    return;
}
