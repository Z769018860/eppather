const char *thread_state_to_string(int *thread_state_ptr, char *buf, int buf_size) {
    int off = 0;
    int thread_state = thread_state_ptr[0];
    int bit_array[8] = {1, 2, 4, 8, 16, 32, 64, 128};  
    int len_array[8] = {1, 1, 1, 1, 1, 1, 1, 1}; 
    char str_array[8] = {'A','B','C','D','E','F','G','H'}; 

    if (buf == 0 || buf_size == 0) {
        return "";
    }

    buf_size = buf_size - 1;

    int index = 0;
    while (thread_state != 0) {
        int bit = bit_array[index];
        if ((thread_state & bit) == 0) {
            index = index + 1;
            continue;
        }

        buf[off] = str_array[index]; 
        off = off + len_array[index];

        thread_state = thread_state & (~bit);

        if (thread_state != 0) {
            buf[off] = '+';
            off = off + 1;
        }

        index = index + 1;
    }

    buf[off] = '\0';
    return buf;
}
