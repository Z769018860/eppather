int probmems_short_circuit(int x, int y, int z) {
    int result = 0;
    if ((x > 0) && ((y > 0) || (z == 0))) {
        result = x + y;
    } else {
        result = z;
    }
    return result;
}
