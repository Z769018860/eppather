int func() {
    char string[13] = {'H','e','l','l','o',',',' ','w','o','r','l','d','!'};
    int length = 0;
    char *p = string;
    for (; *p != '\0'; p = p + 1) {
        length = length + 1;
    }
    return;
}
