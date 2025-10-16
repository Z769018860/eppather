int sma(int action, int period, int handle, int value_index, double value, double values[5], double sum, int lv, double sma_val) {
    double temp_sum;
    int temp_lv;
    int temp_period;
    double temp_values[5];
    
    if (action == 0) {
        for (int i = 0; i < 5; i = i + 1) {
            temp_values[i] = 0.0;
        }
        sma_val = 0.0;
        temp_period = period;
        temp_lv = 0;
        temp_sum = 0.0;
    } else if (action == 1) {
        for (int i = 0; i < 5; i = i + 1) {
            temp_values[i] = 0.0;
        }
        sma_val = 0.0;
        temp_period = 0;
        temp_lv = 0;
        temp_sum = 0.0;
    } else if (action == 2) {
        for (int i = 0; i < 5; i = i + 1) {
            values[i] = temp_values[i];
        }
    } else if (action == 3) {
        sma_val = temp_sum;
    } else if (action == 4) {
        if (temp_lv < temp_period) {
            temp_values[temp_lv] = value;
            temp_lv = temp_lv + 1;
            temp_sum = temp_sum + value;
            sma_val = temp_sum / temp_lv;
        } else {
            temp_sum = temp_sum - temp_values[temp_lv % temp_period];
            temp_sum = temp_sum + value;
            sma_val = temp_sum / temp_period;
            temp_values[temp_lv % temp_period] = value;
            temp_lv = temp_lv + 1;
        }
    }
    return 0;
}
