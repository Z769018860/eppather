void dfs_recursive(int children[3][3], int id[3], int current) {
    if (id[current] > 0) {
        for (int i = 0; i < 3; i = i + 1) {
            dfs_recursive(children, id, children[current][i]);
        }
    }
    return;
}

void dfs_recursive_postorder(int children[3][3], int id[3], int current) {
    for (int i = 0; i < 3; i = i + 1) {
        dfs_recursive_postorder(children, id, children[current][i]);
    }
    return;
}

void dfs_recursive_inorder_btree(int children[3][3], int id[3], int current) {
    if (children[current][0] != -1 && children[current][1] != -1) {
        dfs_recursive_inorder_btree(children, id, children[current][0]);
        dfs_recursive_inorder_btree(children, id, children[current][1]);
    }
    else if (children[current][0] != -1) {
        dfs_recursive_inorder_btree(children, id, children[current][0]);
    }
    return;
}

void dfs_stack(int children[3][3], int id[3], int stack[10], int stack_top) {
    stack[stack_top] = 0;
    stack_top = stack_top + 1;
    int tmp;
    while (stack_top > 0) {
        stack_top = stack_top - 1;
        tmp = stack[stack_top];
        for (int i = 0; i < 3; i = i + 1) {
            stack[stack_top] = children[tmp][i];
            stack_top = stack_top + 1;
        }
    }
    return;
}

void bfs_queue(int children[3][3], int id[3], int queue[10], int queue_front, int queue_rear) {
    queue[queue_rear] = 0;
    queue_rear = queue_rear + 1;
    int tmp;
    while (queue_front < queue_rear) {
        tmp = queue[queue_front];
        queue_front = queue_front + 1;
        for (int i = 0; i < 3; i = i + 1) {
            queue[queue_rear] = children[tmp][i];
            queue_rear = queue_rear + 1;
        }
    }
    return;
}
