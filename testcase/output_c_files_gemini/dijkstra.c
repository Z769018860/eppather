void dijkstra(int graph[5][5], int src)
{
    int dist[5];
    int sptSet[5];
    int i;
    int count;
    int v;
    int u;
    int min;
    int INF;
    INF = 2147483647;
    for (i = 0; i < 5; i = i + 1)
    {
        dist[i] = INF;
        sptSet[i] = 0;
    }
    dist[src] = 0;
    for (count = 0; count < 4; count = count + 1)
    {
        min = INF;
        u = 0;
        for (v = 0; v < 5; v = v + 1)
        {
            if (sptSet[v] == 0 && dist[v] <= min)
            {
                min = dist[v];
                u = v;
            }
        }
        sptSet[u] = 1;
        for (v = 0; v < 5; v = v + 1)
        {
            if (sptSet[v] == 0 && graph[u][v] != 0 && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    return;
}
