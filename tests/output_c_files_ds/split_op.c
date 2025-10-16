void split_op(int par_res, int par_timesteps, int par_im_time, double par_dx, double par_dt, int opr_size, double complex opr_pe[256], double complex opr_ke[256], double complex opr_wfc[256], double opr_v[256]) {
    double density[256];
    double complex y[256];
    int n;
    int i;
    int j;
    int k;
    double sum;
    double complex temp;

    for (i = 0; i < par_timesteps; i = i + 1) {
        for (j = 0; j < opr_size; j = j + 1) {
            opr_wfc[j] = opr_wfc[j] * opr_pe[j];
        }

        for (j = 0; j < opr_size; j = j + 1) {
            y[j] = 0;
        }
        for (j = 0; j < opr_size; j = j + 1) {
            for (k = 0; k < opr_size; k = k + 1) {
                temp.real = cos(-2 * 3.14159265358979323846 * j * k / opr_size);
                temp.imag = sin(-2 * 3.14159265358979323846 * j * k / opr_size);
                y[j] = y[j] + opr_wfc[k] * temp;
            }
            y[j].real = y[j].real / sqrt(opr_size);
            y[j].imag = y[j].imag / sqrt(opr_size);
        }
        for (j = 0; j < opr_size; j = j + 1) {
            opr_wfc[j] = y[j];
        }

        for (j = 0; j < opr_size; j = j + 1) {
            opr_wfc[j] = opr_wfc[j] * opr_ke[j];
        }

        for (j = 0; j < opr_size; j = j + 1) {
            y[j] = 0;
        }
        for (j = 0; j < opr_size; j = j + 1) {
            for (k = 0; k < opr_size; k = k + 1) {
                temp.real = cos(2 * 3.14159265358979323846 * j * k / opr_size);
                temp.imag = sin(2 * 3.14159265358979323846 * j * k / opr_size);
                y[j] = y[j] + opr_wfc[k] * temp;
            }
            y[j].real = y[j].real / sqrt(opr_size);
            y[j].imag = y[j].imag / sqrt(opr_size);
        }
        for (j = 0; j < opr_size; j = j + 1) {
            opr_wfc[j] = y[j];
        }

        for (j = 0; j < opr_size; j = j + 1) {
            opr_wfc[j] = opr_wfc[j] * opr_pe[j];
        }

        for (j = 0; j < opr_size; j = j + 1) {
            density[j] = opr_wfc[j].real * opr_wfc[j].real + opr_wfc[j].imag * opr_wfc[j].imag;
        }

        if (par_im_time != 0) {
            sum = 0;
            for (j = 0; j < opr_size; j = j + 1) {
                sum = sum + density[j];
            }
            sum = sum * par_dx;
            for (j = 0; j < opr_size; j = j + 1) {
                opr_wfc[j].real = opr_wfc[j].real / sqrt(sum);
                opr_wfc[j].imag = opr_wfc[j].imag / sqrt(sum);
            }
        }
    }
    return;
}
