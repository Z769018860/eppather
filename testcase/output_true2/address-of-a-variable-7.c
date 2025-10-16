int read_as_float(int i, int f[1]) {
    int temp[1];
    temp[0] = i;
    f[0] = temp[0];
    return;
}

int main() {
    int i[1];
    i[0] = 168496691;
    int f[1];
    read_as_float(i[0], f);
    return;
}
