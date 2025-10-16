void process_clusters(int map[225], int w, int p) {
    int thresh = 32767 * p / 100;
    int ww = w * w;
    int i;
    int j;
    int cls;
    int x;
    int v;
    int s[225];
    
    for (i = 0; i < ww; i = i + 1) {
        map[i] = -(rand() < thresh);
    }
    
    for (cls = 0, i = 0; i < ww; i = i + 1) {
        if (-1 != map[i]) {
            continue;
        }
        v = cls + 1;
        cls = cls + 1;
        map[i] = v;
        for (x = i - w; x >= 0 && x < ww && map[x] == -1; ) {
            map[x] = v;
            x = x - w;
        }
        for (x = i - 1; x >= 0 && x < ww && map[x] == -1; ) {
            map[x] = v;
            x = x - 1;
        }
        for (x = i + 1; x >= 0 && x < ww && map[x] == -1; ) {
            map[x] = v;
            x = x + 1;
        }
        for (x = i + w; x >= 0 && x < ww && map[x] == -1; ) {
            map[x] = v;
            x = x + w;
        }
    }
    
    for (i = 0; i < w; i = i + 1) {
        for (j = 0; j < w; j = j + 1) {
            s[i * w + j] = map[i * w + j];
        }
    }
    
    return;
}
