int func() {
    int q[100000000];
    int front = 0;
    int rear = 0;
    int i;
    int n;
    
    for (i = 0; i < 100000000; i = i + 1) {
        n = i * 1103515245 + 12345;
        if (n > 16383) {
            q[rear] = n;
            rear = rear + 1;
        } else {
            if (front == rear) {
                continue;
            }
            n = q[front];
            front = front + 1;
        }
    }
    
    for (; front != rear; front = front + 1) {
        n = q[front];
    }
    
    return;
}
