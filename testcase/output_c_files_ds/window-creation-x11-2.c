int xcb_example() {
    int c;
    int screen;
    int win;
    int foreground;
    int background;
    int e;
    int mask;
    int values[2];
    char string[12] = {'H','e','l','l','o',',',' ','X','C','B','!','\0'};
    int string_len = 11;
    int rectangles[4] = {40, 40, 20, 20};

    c = 0;
    screen = 0;
    win = 0;
    foreground = 0;
    background = 0;
    e = 0;
    mask = 0;
    values[0] = 0;
    values[1] = 0;

    foreground = 1;
    mask = 1 | 2;
    values[0] = 0;
    values[1] = 0;

    background = 2;
    mask = 4 | 2;
    values[0] = 1;
    values[1] = 0;

    win = 3;
    mask = 8 | 16;
    values[0] = 1;
    values[1] = 32 | 64;

    for (;;) {
        e = 1;
        if ((e & ~128) == 12) {
            e = 1;
            e = 2;
        } else if ((e & ~128) == 2) {
            break;
        }
    }

    return;
}
