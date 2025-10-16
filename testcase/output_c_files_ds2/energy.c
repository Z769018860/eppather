void calculate_energy(int wfc_real[5], int wfc_imag[5], int h_r_real[5], int h_r_imag[5], int h_k_real[5], int h_k_imag[5], int dx, int size) {
    int wfc_k_real[5];
    int wfc_k_imag[5];
    int wfc_c_real[5];
    int wfc_c_imag[5];
    int energy_k_real[5];
    int energy_k_imag[5];
    int energy_r_real[5];
    int energy_r_imag[5];
    int energy_final[5];
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        wfc_k_real[i] = wfc_real[i];
        wfc_k_imag[i] = wfc_imag[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        wfc_c_real[i] = wfc_real[i];
        wfc_c_imag[i] = -wfc_imag[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        energy_k_real[i] = wfc_k_real[i] * h_k_real[i] - wfc_k_imag[i] * h_k_imag[i];
        energy_k_imag[i] = wfc_k_real[i] * h_k_imag[i] + wfc_k_imag[i] * h_k_real[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        energy_k_real[i] = energy_k_real[i] * wfc_c_real[i] - energy_k_imag[i] * wfc_c_imag[i];
        energy_k_imag[i] = energy_k_real[i] * wfc_c_imag[i] + energy_k_imag[i] * wfc_c_real[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        energy_r_real[i] = (wfc_c_real[i] * h_r_real[i] - wfc_c_imag[i] * h_r_imag[i]) * wfc_real[i] - 
                          (wfc_c_real[i] * h_r_imag[i] + wfc_c_imag[i] * h_r_real[i]) * wfc_imag[i];
        energy_r_imag[i] = (wfc_c_real[i] * h_r_real[i] - wfc_c_imag[i] * h_r_imag[i]) * wfc_imag[i] + 
                          (wfc_c_real[i] * h_r_imag[i] + wfc_c_imag[i] * h_r_real[i]) * wfc_real[i];
    }
    
    energy_final[0] = 0;
    for (i = 0; i < 5; i = i + 1) {
        energy_final[0] = energy_final[0] + (energy_k_real[i] + energy_r_real[i]);
    }
    
    energy_final[0] = energy_final[0] * dx;
    return;
}
