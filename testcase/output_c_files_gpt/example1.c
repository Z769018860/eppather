int isValidNetmask(int netmask) {
    int mask;
    if (netmask == -1 || netmask == 0) {
        return 0;
    }

    mask = ~netmask;
    mask = mask + 1;

    if ((mask & (mask - 1)) == 0) {
        return 1;
    } else {
        return 0;
    }
}
