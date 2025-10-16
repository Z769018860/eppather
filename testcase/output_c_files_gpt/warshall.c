void floydWarshall() {
    int V = 4;
    int INF = 2147483647;
    int graph[4][4] = {{0, 5, INF, 10},
                       {INF, 0, 3, INF},
                       {INF, INF, 0, 1},
                       {INF, INF, INF, 0}};
    int dist[4][4];
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i < V; i = i + 1) {
        for (j = 0; j < V; j = j + 1) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = INF;
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
            }
        }
    }

    return;
}
