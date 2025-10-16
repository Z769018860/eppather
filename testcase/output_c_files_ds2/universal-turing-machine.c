void run(int states_len, int final_states_len, int symbols_len, int blank, int state, int tape_len, int transitions_len) {
    int state_index[5];
    int symbol_index[5];
    int final_states[5];
    int transitions[5][5][5];
    int tape[5];
    int dir[5];
    int i;
    int j;
    int k;
    
    for (i = 0; i < 5; i = i + 1) {
        state_index[i] = 0;
        symbol_index[i] = 0;
        final_states[i] = 0;
        tape[i] = 0;
        dir[i] = 0;
        for (j = 0; j < 5; j = j + 1) {
            for (k = 0; k < 5; k = k + 1) {
                transitions[i][j][k] = 0;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < final_states_len) {
            if (final_states[i] == state) {
                return;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < transitions_len) {
            tape[0] = transitions[state][tape[0]][2];
            if (transitions[state][tape[0]][3] == 0) {
                if (tape[0] > 0) {
                    tape[0] = tape[0] - 1;
                }
            } else if (transitions[state][tape[0]][3] == 1) {
                if (tape[0] < 4) {
                    tape[0] = tape[0] + 1;
                }
            }
            state = transitions[state][tape[0]][4];
        }
    }
    
    return;
}
