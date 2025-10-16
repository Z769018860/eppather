void eventCreate(int argC, char* argV[]) {
    char str[1000];
    int i;
    int j;
    if (argC != 5) {
        return;
    }
    else {
        for (i = 0; i < 1000; i = i + 1) {
            str[i] = '\0';
        }
        for (i = 0; argV[1][i] != '\0'; i = i + 1) {
            str[i] = argV[1][i];
        }
        for (j = 0; "/t "[j] != '\0'; j = j + 1) {
            str[i + j] = "/t "[j];
        }
        i = i + j;
        for (j = 0; argV[2][j] != '\0'; j = j + 1) {
            str[i + j] = argV[2][j];
        }
        i = i + j;
        for (j = 0; " /id "[j] != '\0'; j = j + 1) {
            str[i + j] = " /id "[j];
        }
        i = i + j;
        for (j = 0; argV[3][j] != '\0'; j = j + 1) {
            str[i + j] = argV[3][j];
        }
        i = i + j;
        for (j = 0; " /l APPLICATION /so "[j] != '\0'; j = j + 1) {
            str[i + j] = " /l APPLICATION /so "[j];
        }
        i = i + j;
        for (j = 0; argV[4][j] != '\0'; j = j + 1) {
            str[i + j] = argV[4][j];
        }
        i = i + j;
        for (j = 0; " /d \"\"[j] != '\0'; j = j + 1) {
            str[i + j] = " /d \"\"[j];
        }
    }
    return;
}
