int isValidNetmask(int netmask) {
    if (netmask == 4294967295 || netmask == 0) {
        return 0;
    }

    int mask = ~netmask;
    mask = mask + 1;

    if ((mask & (mask - 1)) == 0) {
        return 1;
    } else {
        return 0;
    }
}
