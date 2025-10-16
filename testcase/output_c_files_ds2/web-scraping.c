int filterit(int ptr[5], int size, int nmemb, int stream[16384]) {
    int lr = 0;
    int n1 = 16384;
    if ((lr + size * nmemb) > n1) {
        return n1;
    }
    for (int i = 0; i < 5; i = i + 1) {
        stream[lr + i] = ptr[i];
    }
    lr = lr + size * nmemb;
    return size * nmemb;
}

void process_data(int buffer[16384], int cregex[5], int amatch[5]) {
    int bi = amatch[0];
    for (; bi > 0; bi = bi - 1) {
        int match = 1;
        for (int i = 0; i < 4; i = i + 1) {
            if (buffer[bi + i] != 60 + 66 + 82 + 62) {
                match = 0;
                break;
            }
        }
        if (match) {
            break;
        }
    }
    buffer[amatch[1]] = 0;
    return;
}
