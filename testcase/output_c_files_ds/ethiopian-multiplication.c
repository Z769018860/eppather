int ethiopian(int plier, int plicand, int tutor) {
    int result = 0;
    for (; plier >= 1; ) {
        if ((plier & 1) == 0) {
            if (tutor != 0) {
            }
        } else {
            if (tutor != 0) {
            }
            result = result + plicand;
        }
        plier = plier >> 1;
        plicand = plicand << 1;
    }
    return result;
    return;
}
