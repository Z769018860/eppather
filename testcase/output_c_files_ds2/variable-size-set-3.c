int interesting_datum[5];
int padding[512];

void func() {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        interesting_datum[i] = 0;
    }
    for (i = 0; i < 512; i = i + 1) {
        padding[i] = 0;
    }
    return;
}
