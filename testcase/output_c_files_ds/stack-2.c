void stack_operations(int operations[100], int data[100], int results[100]) {
    int stack_bottom[100];
    int stack_top = -1;
    int stack_allocated_top = 99;
    int i;
    for (i = 0; i < 100; i = i + 1) {
        if (operations[i] == 0) {
            if (stack_top < 0) {
                results[i] = 1;
            } else {
                results[i] = 0;
            }
        } else if (operations[i] == 1) {
            if (stack_top == stack_allocated_top) {
                int new_qtty = 2 * (stack_top + 1);
                if (new_qtty > 100) {
                    new_qtty = 100;
                }
                stack_allocated_top = new_qtty - 1;
            }
            stack_top = stack_top + 1;
            stack_bottom[stack_top] = data[i];
        } else if (operations[i] == 2) {
            results[i] = stack_bottom[stack_top];
            stack_top = stack_top - 1;
        } else if (operations[i] == 3) {
            if (stack_top != stack_allocated_top) {
                int qtty = stack_top + 1;
                if (qtty < 1) {
                    qtty = 1;
                }
                stack_allocated_top = qtty - 1;
            }
        }
    }
    return;
}
