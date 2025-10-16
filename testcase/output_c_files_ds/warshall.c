void floydWarshall(int V, int graph[100][100]) {
    int dist[100][100];
    for (int i = 0; i < V; i = i + 1) {
        for (int j = 0; j < V; j = j + 1) {
            if (graph[i][j] == 0 && i != j) {
                dist[i][j] = 2147483647;
            }
            else {
                dist[i][j] = graph[i][j];
            }
        }
    }
    for (int k = 0; k < V; k = k + 1) {
        for (int i = 0; i < V; i = i + 1) {
            for (int j = 0; j < V; j = j + 1) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    if (dist[i][k] != 2147483647 && dist[k][j] != 2147483647) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    return;
}
