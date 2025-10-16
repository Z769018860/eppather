double calculate_energy(double complex *wfc, double complex *h_r, double complex *h_k, double dx, int size) {
    double complex wfc_k[1000];
    double complex wfc_c[1000];
    double complex energy_k[1000];
    double complex energy_r[1000];
    double energy_final;
    int i;
    int j;
    int n;
    double complex y[1000];
    double complex x[1000];
    int inverse;
    double complex tmp;

    for (i = 0; i < size; i = i + 1) {
        wfc_k[i] = wfc[i];
    }

    for (i = 0; i < size; i = i + 1) {
        y[i] = 0;
    }
    inverse = 0;
    for (i = 0; i < size; i = i + 1) {
        x[i] = wfc_k[i];
    }
    for (i = 0; i < size; i = i + 1) {
        y[i] = 0;
    }
    for (i = 0; i < size; i = i + 1) {
        tmp = 0;
        for (j = 0; j < size; j = j + 1) {
            tmp = tmp + x[j] * cexp(-I * 2 * M_PI * i * j / size);
        }
        y[i] = tmp;
    }
    for (i = 0; i < size; i = i + 1) {
        wfc_k[i] = y[i];
    }

    for (i = 0; i < size; i = i + 1) {
        wfc_c[i] = conj(wfc[i]);
    }

    for (i = 0; i < size; i = i + 1) {
        energy_k[i] = wfc_k[i] * h_k[i];
    }

    for (i = 0; i < size; i = i + 1) {
        y[i] = 0;
    }
    inverse = 1;
    for (i = 0; i < size; i = i + 1) {
        x[i] = energy_k[i];
    }
    for (i = 0; i < size; i = i + 1) {
        y[i] = 0;
    }
    for (i = 0; i < size; i = i + 1) {
        tmp = 0;
        for (j = 0; j < size; j = j + 1) {
            tmp = tmp + x[j] * cexp(I * 2 * M_PI * i * j / size);
        }
        y[i] = tmp / size;
    }
    for (i = 0; i < size; i = i + 1) {
        energy_k[i] = y[i];
    }

    for (i = 0; i < size; i = i + 1) {
        energy_k[i] = energy_k[i] * wfc_c[i];
        energy_r[i] = wfc_c[i] * h_r[i] * wfc[i];
    }

    energy_final = 0;
    for (i = 0; i < size; i = i + 1) {
        energy_final = energy_final + creal(energy_k[i] + energy_r[i]);
    }

    return energy_final * dx;
}
