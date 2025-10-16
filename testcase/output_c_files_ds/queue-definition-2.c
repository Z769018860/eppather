int queue_operations(int operation, int value, int queue_data[100], int head_index, int tail_index, int* success_flag) {
    if (operation == 0) {
        head_index = 0;
        tail_index = 0;
        *success_flag = 1;
    }
    else if (operation == 1) {
        if (head_index == tail_index) {
            *success_flag = 0;
        }
        else {
            *success_flag = 1;
        }
    }
    else if (operation == 2) {
        queue_data[tail_index] = value;
        tail_index = tail_index + 1;
        *success_flag = 1;
    }
    else if (operation == 3) {
        if (head_index == tail_index) {
            *success_flag = 0;
        }
        else {
            *success_flag = 1;
            value = queue_data[head_index];
            head_index = head_index + 1;
        }
    }
    return;
}
