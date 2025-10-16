void kruskal(int numVertices, int numEdges, int edgeData[][3]) {
    int edges[100][3];
    int parent[10];
    int mstWeight = 0;
    int i = 0;
    int j = 0;

    for (i = 0; i < numVertices; i = i + 1) {
        parent[i] = i;
    }

    for (i = 0; i < numEdges; i = i + 1) {
        edges[i][0] = edgeData[i][0];
        edges[i][1] = edgeData[i][1];
        edges[i][2] = edgeData[i][2];
    }

    for (i = 0; i < numEdges; i = i + 1) {
        for (j = i + 1; j < numEdges; j = j + 1) {
            if (edges[i][2] > edges[j][2]) {
                int temp0 = edges[i][0];
                int temp1 = edges[i][1];
                int temp2 = edges[i][2];
                edges[i][0] = edges[j][0];
                edges[i][1] = edges[j][1];
                edges[i][2] = edges[j][2];
                edges[j][0] = temp0;
                edges[j][1] = temp1;
                edges[j][2] = temp2;
            }
        }
    }

    for (i = 0; i < numEdges; i = i + 1) {
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];
        int rootU = u;
        int rootV = v;

        while (parent[rootU] != rootU) {
            rootU = parent[rootU];
        }

        while (parent[rootV] != rootV) {
            rootV = parent[rootV];
        }

        if (rootU != rootV) {
            mstWeight = mstWeight + weight;
            parent[rootU] = rootV;
        }
    }

    return;
}
