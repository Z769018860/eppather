int turing_machine(int input_state, int input_symbol, int input_dir, int input_tape[5], int tape_len) {
    int states[4] = {0, 1, 2, 3};
    int final_states[1] = {3};
    int symbols[2] = {0, 1};
    int blank = 0;
    int state = input_state;
    int tape[5] = {0, 0, 0, 0, 0};
    int transitions[4][2][5] = {
        {{0, 1, 1, 1, 0}, {0, 0, 0, 2, 2}},
        {{1, 0, 1, 0, 0}, {1, 1, 1, 1, 1}},
        {{2, 0, 1, 0, 1}, {2, 1, 0, 2, 3}},
        {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}}
    };
    int head_pos = 2;
    
    for (int i = 0; i < tape_len; i = i + 1) {
        if (i < 5) {
            tape[head_pos + i - 2] = input_tape[i];
        }
    }
    
    for (int step = 0; step < 100; step = step + 1) {
        int symbol = tape[head_pos];
        int found_final = 0;
        
        for (int i = 0; i < 1; i = i + 1) {
            if (final_states[i] == state) {
                found_final = 1;
            }
        }
        
        if (found_final) {
            break;
        }
        
        int new_symbol = transitions[state][symbol][1];
        int dir = transitions[state][symbol][3];
        int new_state = transitions[state][symbol][4];
        
        tape[head_pos] = new_symbol;
        state = new_state;
        
        if (dir == 1) {
            if (head_pos < 4) {
                head_pos = head_pos + 1;
            }
        } else if (dir == 0) {
            if (head_pos > 0) {
                head_pos = head_pos - 1;
            }
        }
    }
    
    return state;
}
