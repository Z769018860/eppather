void queue_operations(int buf[5], int head, int tail, int alloc, int n, int op, int result[1]) {
    int temp_buf[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        temp_buf[i] = buf[i];
    }
    
    if (op == 0) {
        if (tail >= alloc) {
            tail = 0;
        }
        temp_buf[tail] = n;
        tail = tail + 1;
        if (tail == alloc) {
            if (head != 0) {
                for (i = head; i < alloc; i = i + 1) {
                    temp_buf[i + alloc] = temp_buf[i];
                }
                head = head + alloc;
            } else {
                tail = alloc;
            }
            alloc = alloc * 2;
        }
    } else if (op == 1) {
        if (head == tail) {
            result[0] = 0;
            return;
        }
        result[0] = temp_buf[head];
        head = head + 1;
        if (head >= alloc) {
            head = 0;
            if (alloc >= 512 && tail < alloc / 2) {
                alloc = alloc / 2;
            }
        }
        result[0] = 1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        buf[i] = temp_buf[i];
    }
    return;
}
