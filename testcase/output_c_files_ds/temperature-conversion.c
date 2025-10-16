int kelvin_conversion(int kelvin, int mode) {
    int result;
    if (mode == 0) {
        result = kelvin - 27315;
    }
    else if (mode == 1) {
        result = kelvin * 180 - 45967;
    }
    else if (mode == 2) {
        result = kelvin * 180;
    }
    else {
        result = kelvin;
    }
    return result;
}

void convert_kelvin(int kelvin) {
    int celsius;
    int fahrenheit;
    int rankine;
    
    celsius = kelvin_conversion(kelvin, 0);
    fahrenheit = kelvin_conversion(kelvin, 1);
    rankine = kelvin_conversion(kelvin, 2);
    
    return;
}
