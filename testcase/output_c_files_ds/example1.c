int function(int netmask) {
    int result;
    if (netmask == 0xFFFFFFFF) {
        result = 0;
    } else {
        if (netmask == 0) {
            result = 0;
        } else {
            int mask;
            mask = ~netmask;
            mask = mask + 1;
            int temp;
            temp = mask - 1;
            if ((mask & temp) == 0) {
                result = 1;
            } else {
                result = 0;
            }
        }
    }
    return result;
}
