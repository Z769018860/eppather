int m_enqueue(int value, int* head) {
    int temp[20];
    int i;
    for (i = 0; i < 20; i = i + 1) {
        if (head[i] == 0) {
            head[i] = value;
            break;
        }
    }
    return;
}

int m_dequeue(int* value, int* head) {
    int i;
    if (head[0] == 0) {
        return 0;
    }
    *value = head[0];
    for (i = 0; i < 19; i = i + 1) {
        head[i] = head[i + 1];
    }
    head[19] = 0;
    return 1;
}

void fifo_test() {
    int head[20] = {0};
    int i;
    int value;
    
    for (i = 0; i < 20; i = i + 1) {
        m_enqueue(i, head);
    }
    
    for (i = 0; i < 20; i = i + 1) {
        m_dequeue(&value, head);
    }
    
    m_dequeue(&value, head);
    return;
}
