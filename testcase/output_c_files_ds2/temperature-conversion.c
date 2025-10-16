void convertKelvin(int kelvin[5]) {
    int celsius[5];
    int fahrenheit[5];
    int rankine[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        celsius[i] = kelvin[i] - 27315 / 100;
        fahrenheit[i] = kelvin[i] * 180 / 100 - 45967 / 100;
        rankine[i] = kelvin[i] * 180 / 100;
    }
    return;
}
