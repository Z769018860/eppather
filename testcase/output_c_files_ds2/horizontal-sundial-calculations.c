void calculateSunDial(int lat, int lng, int ref) {
    int slat[5];
    int hla[5];
    int hra[5];
    int h;
    int pi = 314159265;
    int dr[5];
    int rd[5];
    
    dr[0] = lat * pi / 180000000;
    slat[0] = 1000 * dr[0] / 1000;
    
    for (h = -6; h <= 6; h = h + 1) {
        hra[0] = 150 * h;
        hra[0] = hra[0] - lng + ref;
        dr[0] = hra[0] * pi / 180000000;
        hla[0] = 180000000 * slat[0] * dr[0] / pi;
    }
    return;
}
