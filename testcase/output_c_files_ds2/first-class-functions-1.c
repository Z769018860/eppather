int functionA(int v[5]) {
    v[0] = v[0] * v[0] * v[0];
    return v[0];
}

int functionB(int v[5]) {
    int x[5];
    x[0] = 1;
    for (int i = 0; i < 5; i = i + 1) {
        if (v[0] > 0) {
            x[0] = x[0] * v[0];
        }
    }
    v[0] = x[0];
    return v[0];
}

int Function1(int (*f2)(int[5]), int val[5]) {
    return f2(val);
}

int WhichFunc(int idx[5]) {
    if (idx[0] < 4) {
        return 0;
    } else {
        return 1;
    }
}

int InvokeComposed(int (*f1)(int[5]), int (*f2)(int[5]), int val[5]) {
    int temp[5];
    temp[0] = val[0];
    temp[0] = f2(temp);
    temp[0] = f1(temp);
    return temp[0];
}

int Compose(int f1[5], int f2[5], int comp[5]) {
    comp[0] = f1[0];
    comp[1] = f2[0];
    return 0;
}

int CallComposed(int comp[5], int val[5]) {
    int temp[5];
    temp[0] = val[0];
    temp[0] = comp[1];
    temp[0] = comp[0];
    return temp[0];
}

int main() {
    int ix[5];
    int c[5];
    int val[5];
    val[0] = 3;
    ix[0] = 0;
    Function1(WhichFunc(ix), val);
    for (ix[0] = 0; ix[0] < 5; ix[0] = ix[0] + 1) {
        int funcListA[5];
        int funcListB[5];
        Compose(funcListA, funcListB, c);
        val[0] = 0;
        CallComposed(c, val);
    }
    return 0;
}
