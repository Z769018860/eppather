void beer_song() {
    int _[5];
    _[0] = 100;
    int temp[5];
    for (; _[0] > 0; _[0] = _[0] - 1) {
        temp[0] = _[0] - 1;
        temp[1] = temp[0] != 0 ? 1 : 0;
        temp[2] = temp[0] != 0 ? 1 : 0;
        temp[3] = temp[0] != 0 ? 1 : 0;
        temp[4] = temp[0] != 0 ? 1 : 0;
        
        for (int i = 0; i < 5; i = i + 1) {
            if (temp[0] > 0) {
                int digit1 = temp[0] / 10;
                int digit2 = temp[0] % 10;
                int chars[4];
                chars[0] = digit1 != 0 ? digit1 + 48 : digit2 + 48;
                chars[1] = digit1 != 0 ? digit2 + 48 : 50 + 30;
                chars[2] = digit1 != 0 ? 32 : 0;
                chars[3] = 0;
            }
        }
    }
    return;
}
