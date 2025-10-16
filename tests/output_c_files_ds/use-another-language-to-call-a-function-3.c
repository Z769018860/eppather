int process_input(char* input) {
    int i = 0;
    for (i = 0; input[i] != '\0'; i = i + 1) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            input[i] = input[i] - 32;
        }
    }
    return;
}
