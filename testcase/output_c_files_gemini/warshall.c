void floydWarshall() {
    int graph[4][4] = {
        {0, 5, 2147483647, 10},
        {2147483647, 0, 3, 2147483647},
        {2147483647, 2147483647, 0, 1},
        {2147483647, 2147483647, 2147483647, 0}
    };
    int dist[4][4];
    int i;
    int j;
    int k;

    for (i = 0; i < 4; i = i + 1) {
        for (j = 0; j < 4; j = j + 1) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = 2147483647;
            } else {
                dist[i][j] = graph[i][j];
            }
        }
    }

    for (k = 0; k < 4; k = k + 1) {
        for (i = 0; i < 4; i = i + 1) {
            for (j = 0; j < 4; j = j + 1) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return;
}
