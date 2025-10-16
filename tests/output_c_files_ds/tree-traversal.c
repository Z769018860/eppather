void tree_traversal(int* values, int* left_indices, int* right_indices, int root_index, int traversal_type, int* result, int* result_index) {
    int stack[100];
    int stack_top = 0;
    int visited[100];
    int queue[100];
    int queue_front = 0;
    int queue_rear = 0;
    int current = root_index;
    
    if (traversal_type == 0) {
        stack[stack_top] = current;
        stack_top = stack_top + 1;
        while (stack_top > 0) {
            current = stack[stack_top - 1];
            stack_top = stack_top - 1;
            result[*result_index] = values[current];
            *result_index = *result_index + 1;
            if (right_indices[current] != -1) {
                stack[stack_top] = right_indices[current];
                stack_top = stack_top + 1;
            }
            if (left_indices[current] != -1) {
                stack[stack_top] = left_indices[current];
                stack_top = stack_top + 1;
            }
        }
    }
    else if (traversal_type == 1) {
        while (current != -1 || stack_top > 0) {
            while (current != -1) {
                stack[stack_top] = current;
                stack_top = stack_top + 1;
                current = left_indices[current];
            }
            current = stack[stack_top - 1];
            stack_top = stack_top - 1;
            result[*result_index] = values[current];
            *result_index = *result_index + 1;
            current = right_indices[current];
        }
    }
    else if (traversal_type == 2) {
        stack[stack_top] = current;
        stack_top = stack_top + 1;
        while (stack_top > 0) {
            current = stack[stack_top - 1];
            if (left_indices[current] != -1 && visited[left_indices[current]] != 1) {
                stack[stack_top] = left_indices[current];
                stack_top = stack_top + 1;
                current = left_indices[current];
            }
            else if (right_indices[current] != -1 && visited[right_indices[current]] != 1) {
                stack[stack_top] = right_indices[current];
                stack_top = stack_top + 1;
                current = right_indices[current];
            }
            else {
                stack_top = stack_top - 1;
                result[*result_index] = values[current];
                *result_index = *result_index + 1;
                visited[current] = 1;
            }
        }
    }
    else if (traversal_type == 3) {
        queue[queue_rear] = current;
        queue_rear = queue_rear + 1;
        while (queue_front != queue_rear) {
            current = queue[queue_front];
            queue_front = queue_front + 1;
            result[*result_index] = values[current];
            *result_index = *result_index + 1;
            if (left_indices[current] != -1) {
                queue[queue_rear] = left_indices[current];
                queue_rear = queue_rear + 1;
            }
            if (right_indices[current] != -1) {
                queue[queue_rear] = right_indices[current];
                queue_rear = queue_rear + 1;
            }
        }
    }
    return;
}
