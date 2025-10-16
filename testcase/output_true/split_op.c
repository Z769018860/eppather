void split_op(int xmax, int res, int timesteps, int im_time, int voffset, int wfcoffset) {
    int x[5];
    int k[5];
    int v[5];
    int pe[5];
    int ke[5];
    int wfc[5];
    int density[5];
    int y[5];
    int wfc_r[5];
    int wfc_k[5];
    int wfc_c[5];
    int energy_k[5];
    int energy_r[5];
    int sum;
    int energy_final;
    int dt;
    int dx;
    int dk;
    int i;
    int j;
    
    dt = 1;
    dx = 1;
    dk = 1;
    
    for (i = 0; i < 5; i = i + 1) {
        x[i] = 0;
        k[i] = 0;
        v[i] = 0;
        pe[i] = 0;
        ke[i] = 0;
        wfc[i] = 0;
        density[i] = 0;
        y[i] = 0;
        wfc_r[i] = 0;
        wfc_k[i] = 0;
        wfc_c[i] = 0;
        energy_k[i] = 0;
        energy_r[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        x[i] = xmax / res - xmax + i * (2 * xmax / res);
        if (i < res / 2) {
            k[i] = i * 3 / xmax;
        } else {
            k[i] = (i - res) * 3 / xmax;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        v[i] = (x[i] - voffset) * (x[i] - voffset) / 2;
        wfc[i] = 1;
        if (im_time) {
            ke[i] = 1;
            pe[i] = 1;
        } else {
            ke[i] = 1;
            pe[i] = 1;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            wfc[j] = wfc[j] * pe[j];
        }
        
        for (j = 0; j < 5; j = j + 1) {
            wfc[j] = wfc[j] * ke[j];
        }
        
        for (j = 0; j < 5; j = j + 1) {
            wfc[j] = wfc[j] * pe[j];
        }
        
        for (j = 0; j < 5; j = j + 1) {
            density[j] = wfc[j] * wfc[j];
        }
        
        if (im_time) {
            sum = 0;
            for (j = 0; j < 5; j = j + 1) {
                sum = sum + density[j];
            }
            sum = sum * dx;
            for (j = 0; j < 5; j = j + 1) {
                wfc[j] = wfc[j] / sum;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        wfc_r[i] = wfc[i];
        wfc_k[i] = wfc[i];
        wfc_c[i] = wfc[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        energy_k[i] = wfc_k[i] * (k[i] * k[i]);
        energy_r[i] = wfc_c[i] * v[i] * wfc_r[i];
    }
    
    energy_final = 0;
    for (i = 0; i < 5; i = i + 1) {
        energy_final = energy_final + (energy_k[i] + energy_r[i]);
    }
    energy_final = energy_final * dx;
    
    return;
}
