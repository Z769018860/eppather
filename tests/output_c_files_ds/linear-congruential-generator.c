int rseed;

void srand_rand(int x) {
    rseed = x;
    return;
}

int rand() {
    rseed = (rseed * 1103515245 + 12345) & 2147483647;
    return rseed;
    return;
}
