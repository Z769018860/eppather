int sma(int action, int period, int handle, int value) {
    int values[5];
    int sum[5] = {0};
    int lv[5] = {0};
    int sma[5] = {0};
    int v[5] = {0};
    int o[5] = {0};
    int r[5] = {0};
    
    if (action == 0) {
        for (int i = 0; i < 5; i = i + 1) {
            values[i] = 0;
        }
        sum[0] = 0;
        lv[0] = 0;
        sma[0] = 0;
        r[0] = 0;
    } else if (action == 1) {
        for (int i = 0; i < 5; i = i + 1) {
            values[i] = 0;
        }
        r[0] = 0;
    } else if (action == 2) {
        o[0] = handle;
        for (int i = 0; i < 5; i = i + 1) {
            r[i] = values[i];
        }
    } else if (action == 3) {
        o[0] = handle;
        r[0] = sma[0];
    } else if (action == 4) {
        o[0] = handle;
        v[0] = value;
        if (lv[0] < period) {
            values[lv[0]] = v[0];
            sum[0] = sum[0] + v[0];
            lv[0] = lv[0] + 1;
            sma[0] = sum[0] / lv[0];
        } else {
            sum[0] = sum[0] - values[lv[0] % period];
            sum[0] = sum[0] + v[0];
            sma[0] = sum[0] / period;
            values[lv[0] % period] = v[0];
            lv[0] = lv[0] + 1;
        }
        r[0] = sma[0];
    }
    return r[0];
}
