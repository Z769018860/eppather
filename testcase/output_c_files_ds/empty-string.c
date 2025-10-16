int str_empty_test() {
    char str[1] = {'\0'};
    int result = 0;
    
    if (str) {
        result = 1;
    }
    
    if (str[0] == '\0') {
        result = result + 1;
    }
    
    int len = 0;
    for (int i = 0; str[i] != '\0'; i = i + 1) {
        len = len + 1;
    }
    if (len == 0) {
        result = result + 1;
    }
    
    int cmp = 1;
    char empty[1] = {'\0'};
    for (int i = 0; str[i] != '\0' || empty[i] != '\0'; i = i + 1) {
        if (str[i] != empty[i]) {
            cmp = 0;
            break;
        }
    }
    if (cmp == 1) {
        result = result + 1;
    }
    
    return;
}
