void dijkstra(int V, int graph[10][10], int src) {
    int dist[10], sptSet[10];
    int min, u, v, count;

    for (int i = 0; i < V; i = i + 1) {
        dist[i] = 100000;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    for (count = 0; count < V - 1; count = count + 1) {
        min = 100000;
        u = -1;

        for (v = 0; v < V; v = v + 1) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        sptSet[u] = 1;

        for (v = 0; v < V; v = v + 1) {
            if (!sptSet[v] && graph[u][v] && dist[u] != 100000 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    return;
}