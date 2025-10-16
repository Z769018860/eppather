int parent[5];

int find(int i) {
    if (parent[i] != i) {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

int compare(const void* a, const void* b) {
    return ((int*)a)[2] - ((int*)b)[2];
}

void kruskal(int numVertices, int numEdges, int edgeData[5][3]) {
    int edges[100][3];
    int mstWeight = 0;
    int i, u, v, weight;

    for (i = 0; i < numVertices; i = i + 1) {
        parent[i] = i;
    }

    for (i = 0; i < numEdges; i = i + 1) {
        edges[i][0] = edgeData[i][0];
        edges[i][1] = edgeData[i][1];
        edges[i][2] = edgeData[i][2];
    }

    qsort(edges, numEdges, sizeof(edges[0]), compare);

    for (i = 0; i < numEdges; i = i + 1) {
        u = edges[i][0];
        v = edges[i][1];
        weight = edges[i][2];

        if (find(u) != find(v)) {
            mstWeight = mstWeight + weight;
            parent[find(u)] = find(v);
        }
    }
    return;
}
