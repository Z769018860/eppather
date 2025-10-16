double calculateSunDial(int lat, int lng, int ref) {
    double slat;
    double hla;
    double hra;
    int h;
    double pi = 3.14159265358979323846;
    double lat_rad = lat * pi / 180.0;
    slat = sin(lat_rad);
    
    for (h = -6; h <= 6; h = h + 1) {
        hra = 15.0 * h;
        hra = hra - lng + ref;
        double hra_rad = hra * pi / 180.0;
        double tan_hra = tan(hra_rad);
        double atan_val = atan(slat * tan_hra);
        hla = atan_val * 180.0 / pi;
    }
    
    return;
}
