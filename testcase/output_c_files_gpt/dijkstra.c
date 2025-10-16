void dijkstra(int V, int graph[100][100], int src) {
    int dist[100];
    int sptSet[100];
    int i = 0;
    int count = 0;
    int v = 0;
    int min, u;

    for (i = 0; i < V; i = i + 1) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    for (count = 0; count < V - 1; count = count + 1) {
        min = INT_MAX;
        for (v = 0; v < V; v = v + 1) {
            if (sptSet[v] == 0 && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }

        sptSet[u] = 1;

        for (v = 0; v < V; v = v + 1) {
            if (sptSet[v] == 0 && graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    return;
}
