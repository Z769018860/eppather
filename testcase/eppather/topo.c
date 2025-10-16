void topologicalSort(int graph[100][100], int n) {
    int inDegree[100] = {0};
    int stack[100], top = -1;
    int i,j,node;

    for (i = 0; i < n; i = i + 1) {
        for (j = 0; j < n; j = j + 1) {
            if (graph[j][i]) {
                inDegree[i] = inDegree[i] + 1;
            }
            ;
        }
        ;
    }

    for (i = 0; i < n; i = i + 1) {
        if (inDegree[i] == 0) {
            top = top + 1;
            stack[top] = i;
        }
        ;
    }

    while (top != -1) {
        node = stack[top];
        top = top - 1;

        for (i = 0; i < n; i = i + 1) {
            if (graph[node][i]) {
                inDegree[i] = inDegree[i] - 1;
                if (inDegree[i] == 0) {
                    top = top + 1;
                    stack[top] = i;
                }
                ;
            }
            ;
        }
        ;
    }
    return;
}
