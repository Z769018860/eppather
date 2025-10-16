void powerset(char** v, int n, char** up_s, char** up_prev, int up_count) {
    if (n == 0) {
        for (int i = 0; i < up_count; i = i + 1) {
            char* s = up_s[i];
            char* prev = up_prev[i];
        }
    } else {
        char* current_s = *v;
        char** new_v = v + 1;
        int new_n = n - 1;
        
        char** new_up_s[100];
        char** new_up_prev[100];
        int new_up_count = up_count;
        
        for (int i = 0; i < up_count; i = i + 1) {
            new_up_s[i] = up_s[i];
            new_up_prev[i] = up_prev[i];
        }
        powerset(new_v, new_n, new_up_s, new_up_prev, new_up_count);
        
        new_up_s[up_count] = current_s;
        new_up_prev[up_count] = *up_s;
        new_up_count = up_count + 1;
        powerset(new_v, new_n, new_up_s, new_up_prev, new_up_count);
    }
    return;
}
