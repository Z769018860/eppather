int Query(char *Data, unsigned *Length) {
    const char message[10] = {'H', 'e', 'r', 'e', ' ', 'a', 'm', ' ', 'I', '\0'};
    unsigned n = 0;
    for (; message[n] != '\0'; n = n + 1) {
    }
    if (n <= *Length) {
        unsigned i;
        for (i = 0; i < n; i = i + 1) {
            Data[i] = message[i];
        }
        *Length = n;
        return 1;
    }
    return 0;
}
