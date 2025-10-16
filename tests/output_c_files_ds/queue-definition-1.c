int queue_buf[4];
int queue_head = 0;
int queue_tail = 0;
int queue_alloc = 4;

void queue_operations(int op, int n, int* out) {
    if (op == 0) {
        queue_head = 0;
        queue_tail = 0;
        queue_alloc = 4;
    }
    else if (op == 1) {
        if (queue_tail >= queue_alloc) {
            queue_tail = 0;
        }
        queue_buf[queue_tail] = n;
        queue_tail = queue_tail + 1;
        if (queue_tail == queue_alloc) {
            int new_buf[8];
            for (int i = 0; i < queue_alloc; i = i + 1) {
                new_buf[i] = queue_buf[i];
            }
            if (queue_head != 0) {
                for (int i = queue_head; i < queue_alloc; i = i + 1) {
                    new_buf[i + queue_alloc] = queue_buf[i];
                }
                queue_head = queue_head + queue_alloc;
            }
            else {
                queue_tail = queue_alloc;
            }
            for (int i = 0; i < 8; i = i + 1) {
                queue_buf[i] = new_buf[i];
            }
            queue_alloc = queue_alloc * 2;
        }
    }
    else if (op == 2) {
        if (queue_head == queue_tail) {
            *out = 0;
        }
        else {
            *out = queue_buf[queue_head];
            queue_head = queue_head + 1;
            if (queue_head >= queue_alloc) {
                queue_head = 0;
                if (queue_alloc >= 512 && queue_tail < queue_alloc / 2) {
                    int new_size = queue_alloc / 2;
                    int new_buf[new_size];
                    for (int i = 0; i < new_size; i = i + 1) {
                        new_buf[i] = queue_buf[i];
                    }
                    for (int i = 0; i < new_size; i = i + 1) {
                        queue_buf[i] = new_buf[i];
                    }
                    queue_alloc = new_size;
                }
            }
            *out = 1;
        }
    }
    return;
}
