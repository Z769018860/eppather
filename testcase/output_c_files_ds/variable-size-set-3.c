int interesting_datum;
int padding[128];

void func() {
    interesting_datum = 0;
    for (int i = 0; i < 128; i = i + 1) {
        padding[i] = 0;
    }
    return;
}
