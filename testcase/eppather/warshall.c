void floydWarshall(int V, int graph[10][10]) {
    int dist[10][10];
    int i, j, k;

    for (i = 0; i < V; i = i + 1) {
        for (j = 0; j < V; j = j + 1) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = 2147483647;
            } else {
                dist[i][j] = graph[i][j];
            }
        }
    }

    for (k = 0; k < V; k = k + 1) {
        for (i = 0; i < V; i = i + 1) {
            for (j = 0; j < V; j = j + 1) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
                ;
            }
            ;
        }
        ;
    }
    ;
    return;
}
