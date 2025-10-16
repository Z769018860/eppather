int sleep_emulator(unsigned int seconds) {
    int dummy;
    for (unsigned int i = 0; i < seconds; i = i + 1) {
        for (int j = 0; j < 1000000; j = j + 1) {
            dummy = dummy + 1;
        }
    }
    return;
}
