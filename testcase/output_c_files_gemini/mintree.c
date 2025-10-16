void benchmark_kruskal(int numVertices, int numEdges, int edgeData[100][3]) {
    int parent[10];
    int edges[100][3];
    int mstWeight;
    int i;
    int j;
    int u;
    int v;
    int weight;
    int root_u;
    int root_v;
    int path_walker;
    int next_walker;
    int temp_u;
    int temp_v;
    int temp_w;

    mstWeight = 0;

    for (i = 0; i < numVertices; i = i + 1) {
        parent[i] = i;
    }

    for (i = 0; i < numEdges; i = i + 1) {
        edges[i][0] = edgeData[i][0];
        edges[i][1] = edgeData[i][1];
        edges[i][2] = edgeData[i][2];
    }

    for (i = 0; i < numEdges - 1; i = i + 1) {
        for (j = 0; j < numEdges - i - 1; j = j + 1) {
            if (edges[j][2] > edges[j + 1][2]) {
                temp_u = edges[j][0];
                temp_v = edges[j][1];
                temp_w = edges[j][2];
                edges[j][0] = edges[j + 1][0];
                edges[j][1] = edges[j + 1][1];
                edges[j][2] = edges[j + 1][2];
                edges[j + 1][0] = temp_u;
                edges[j + 1][1] = temp_v;
                edges[j + 1][2] = temp_w;
            }
        }
    }

    for (i = 0; i < numEdges; i = i + 1) {
        u = edges[i][0];
        v = edges[i][1];
        weight = edges[i][2];

        root_u = u;
        for (; parent[root_u] != root_u; ) {
            root_u = parent[root_u];
        }
        path_walker = u;
        for (; path_walker != root_u; ) {
            next_walker = parent[path_walker];
            parent[path_walker] = root_u;
            path_walker = next_walker;
        }

        root_v = v;
        for (; parent[root_v] != root_v; ) {
            root_v = parent[root_v];
        }
        path_walker = v;
        for (; path_walker != root_v; ) {
            next_walker = parent[path_walker];
            parent[path_walker] = root_v;
            path_walker = next_walker;
        }

        if (root_u != root_v) {
            mstWeight = mstWeight + weight;
            parent[root_u] = root_v;
        }
    }

    return;
}
