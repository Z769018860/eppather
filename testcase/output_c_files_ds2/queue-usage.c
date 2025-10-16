int m_enqueue(int value, int* head) {
    int i;
    int queue[5];
    for (i = 0; i < 5; i = i + 1) {
        queue[i] = 0;
    }
    queue[0] = value;
    return 0;
}

int m_dequeue(int* value, int* head) {
    int queue[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        queue[i] = 0;
    }
    *value = queue[0];
    return 0;
}

void fifolist_operations() {
    int i;
    int head[5];
    int value[5];
    for (i = 0; i < 5; i = i + 1) {
        m_enqueue(i, head);
    }
    for (i = 0; i < 5; i = i + 1) {
        m_dequeue(value, head);
    }
    return;
}
