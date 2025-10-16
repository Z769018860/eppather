void format_output() {
    int r = 7125;
    int sign = 0;
    int width = 9;
    int precision = 3;
    int i = 0;
    int j = 0;
    int digits[4] = {7, 1, 2, 5};
    int leading_zeros = 0;
    int trailing_zeros = 0;
    int pad_left = 0;
    int pad_right = 0;
    int pad_char = 0;
    int output[12] = {0};

    for (i = 0; i < 6; i = i + 1) {
        sign = 0;
        pad_left = 1;
        pad_right = 0;
        pad_char = 32;
        leading_zeros = 0;
        trailing_zeros = 0;

        if (i == 0 || i == 3) {
            sign = 1;
        }
        if (i == 2 || i == 5) {
            pad_left = 0;
            pad_right = 1;
        }
        if (i == 3 || i == 4) {
            pad_char = 48;
        }

        for (j = 0; j < 12; j = j + 1) {
            output[j] = 32;
        }

        if (sign) {
            output[0] = 45;
        }

        if (pad_left) {
            for (j = sign; j < width - precision - 1 - sign; j = j + 1) {
                output[j] = pad_char;
            }
        }

        for (j = 0; j < 3; j = j + 1) {
            output[width - precision - 1 + j] = digits[j] + 48;
        }
        output[width - precision - 1 + 3] = 46;
        for (j = 0; j < 3; j = j + 1) {
            output[width - precision + 3 + j] = digits[j + 1] + 48;
        }

        if (pad_right) {
            for (j = width - precision + 6; j < width; j = j + 1) {
                output[j] = pad_char;
            }
        }
    }
    return;
}
