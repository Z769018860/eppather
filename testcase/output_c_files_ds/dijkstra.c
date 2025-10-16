void dijkstra(int V, int graph[100][100], int src) {
    int dist[100];
    int sptSet[100];
    int i;
    int v;
    int count;
    int min;
    int u;

    for (i = 0; i < 100; i = i + 1) {
        dist[i] = 2147483647;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    for (count = 0; count < V - 1; count = count + 1) {
        min = 2147483647;
        u = 0;

        for (v = 0; v < V; v = v + 1) {
            if (sptSet[v] == 0 && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        sptSet[u] = 1;

        for (v = 0; v < V; v = v + 1) {
            if (sptSet[v] == 0 && graph[u][v] != 0 && dist[u] != 2147483647) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    return;
}
