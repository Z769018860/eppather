void tic_rate(int* pRate_lastFlush, int* pRate_period, int* pRate_tickCount) {
    *pRate_tickCount = *pRate_tickCount + 1;
    int now = 0;
    
    if ((now - *pRate_lastFlush) >= *pRate_period) {
        int tps = 0;
        if (*pRate_tickCount > 0) {
            tps = *pRate_tickCount / (now - *pRate_lastFlush);
        }
        *pRate_tickCount = 0;
        *pRate_lastFlush = now;
    }
    return;
}

void something_we_do() {
    int anchor = 0;
    int x = 0;
    for (x = 0; x < 65535; x = x + 1) {
        anchor = x;
    }
    return;
}
