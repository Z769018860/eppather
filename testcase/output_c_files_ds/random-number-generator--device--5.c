int generate_random_number() {
    int random_state = 12345;
    int random_number = 0;
    for (int i = 0; i < 32; i = i + 1) {
        random_state = random_state * 1103515245 + 12345;
        random_number = (random_number << 1) | ((random_state >> 16) & 1);
    }
    return random_number;
}
