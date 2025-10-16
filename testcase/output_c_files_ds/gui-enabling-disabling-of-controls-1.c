int process_value(int current_value, int action) {
    int min_value = 0;
    int max_value = 10;
    int new_value = current_value;

    if (action == 1) {
        if (current_value < max_value) {
            new_value = current_value + 1;
        }
    } else {
        if (action == 2) {
            if (current_value > min_value) {
                new_value = current_value - 1;
            }
        }
    }

    return new_value;
}

int check_controls_state(int current_value) {
    int min_value = 0;
    int max_value = 10;
    int state = 0;

    if (current_value < max_value) {
        state = state | 1;
    }
    if (current_value > min_value) {
        state = state | 2;
    }

    return state;
}

void combined_function(int* value, int action) {
    int min_value = 0;
    int max_value = 10;
    
    if (action == 1 || action == 2) {
        *value = process_value(*value, action);
    }
    
    int state = check_controls_state(*value);
    
    return;
}
