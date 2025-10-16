int queue[100];
int head = 0;
int tail = 0;

void m_enqueue(int v) {
    if (tail < 100) {
        queue[tail] = v;
        tail = tail + 1;
    }
    return;
}

void m_dequeue(int *v) {
    if (head < tail) {
        *v = queue[head];
        head = head + 1;
    }
    return;
}

int isQueueEmpty() {
    if (head == tail) {
        return 1;
    }
    return 0;
}
