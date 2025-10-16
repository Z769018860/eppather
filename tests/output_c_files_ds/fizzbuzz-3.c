int func(int num) {
    int result[100];
    for (int i = 0; i < 100; i = i + 1) {
        result[i] = i + 1;
    }
    for (int i = 0; i < 100; i = i + 1) {
        if (result[i] % 15 == 0) {
            result[i] = -1; // FizBuz
        } else if (result[i] % 3 == 0) {
            result[i] = -2; // Fiz
        } else if (result[i] % 5 == 0) {
            result[i] = -3; // Buz
        } else if (result[i] % 7 == 0) {
            result[i] = -4; // Goz
        } else if (result[i] % 11 == 0) {
            result[i] = -5; // Kaz
        } else if (result[i] % 21 == 0) {
            result[i] = -6; // FizKaz
        }
    }
    return;
}
