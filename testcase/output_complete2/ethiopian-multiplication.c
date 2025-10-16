int ethiopian(int plier, int plicand, int tutor) {
    int result[5];
    result[0] = 0;
    int plier_copy[5];
    plier_copy[0] = plier;
    int plicand_copy[5];
    plicand_copy[0] = plicand;

    for (; plier_copy[0] >= 1; ) {
        if ((plicand_copy[0] & 1) == 0) {
            if (tutor != 0) {
            }
        } else {
            if (tutor != 0) {
            }
            result[0] = result[0] + plicand_copy[0];
        }
        plier_copy[0] = plier_copy[0] >> 1;
        plicand_copy[0] = plicand_copy[0] << 1;
    }
    return result[0];
}
