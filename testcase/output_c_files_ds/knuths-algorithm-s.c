int* test(int n, int* items_set, int num_items) {
    int s_env_sample[100];
    int s_env_i = 0;
    int s_env_n = n;
    int s_env_size = sizeof(int);
    int i;
    int j;
    int temp;
    
    for (i = 0; i < num_items; i = i + 1) {
        s_env_i = s_env_i + 1;
        if (s_env_i <= s_env_n) {
            temp = items_set[i];
            for (j = 0; j < s_env_size; j = j + 1) {
                s_env_sample[(s_env_i - 1) * s_env_size + j] = *((char*)&temp + j);
            }
        } else {
            int rand_val = 0;
            for (j = 0; j < 31; j = j + 1) {
                rand_val = (rand_val << 1) | (i & 1);
            }
            if ((rand_val % s_env_i) < s_env_n) {
                int replace_pos = 0;
                for (j = 0; j < 31; j = j + 1) {
                    replace_pos = (replace_pos << 1) | (i & 1);
                }
                replace_pos = replace_pos % s_env_n;
                temp = items_set[i];
                for (j = 0; j < s_env_size; j = j + 1) {
                    s_env_sample[replace_pos * s_env_size + j] = *((char*)&temp + j);
                }
            }
        }
    }
    return s_env_sample;
}
