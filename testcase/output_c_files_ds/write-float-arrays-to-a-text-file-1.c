int func() {
    int x[4] = {1, 2, 3, 100000000000};
    int y[4];
    int i;
    
    for (i = 0; i < 4; i = i + 1) {
        int low = 0;
        int high = x[i];
        int mid;
        int result;
        
        while (low <= high) {
            mid = low + (high - low) / 2;
            if (mid * mid == x[i]) {
                result = mid;
                break;
            } else {
                if (mid * mid < x[i]) {
                    low = mid + 1;
                    result = mid;
                } else {
                    high = mid - 1;
                }
            }
        }
        y[i] = result;
    }
    
    return;
}
