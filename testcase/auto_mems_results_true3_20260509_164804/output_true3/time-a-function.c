int identity(int x[5]) {
    return x[0];
}

int sum(int s[5]) {
    int i;
    int n1;
    n1 = 1000000;
    for (i = 0; i < n1; i = i + 1) {
        s[0] = s[0] + i;
    }
    return s[0];
}

int time_it(int action(int[5]), int arg[5]) {
    int elaps_s[5];
    int elaps_ns[5];
    elaps_s[0] = 0;
    elaps_ns[0] = 0;
    action(arg);
    elaps_s[0] = 0;
    elaps_ns[0] = 0;
    return 0;
}

int main() {
    int x[5];
    x[0] = 4;
    time_it(identity, x);
    time_it(sum, x);
    return 0;
}
