void timeFunctions(int inputs, int set_hour[5], int set_minute[5], int set_second[5], int meanTime[3]) {
    double angleSet[5];
    double y_part = 0;
    double x_part = 0;
    double angleMean;
    double totalSeconds;
    int i;
    
    for (i = 0; i < 5; i = i + 1) {
        angleSet[i] = (360 * set_hour[i] / 24.0 + 360 * set_minute[i] / (24 * 60.0) + 360 * set_second[i] / (24 * 3600.0));
    }
    
    for (i = 0; i < 5; i = i + 1) {
        x_part = x_part + (angleSet[i] * 3.141592653589793 / 180);
        y_part = y_part + (angleSet[i] * 3.141592653589793 / 180);
    }
    
    angleMean = (y_part / 5) / (x_part / 5) * 180 / 3.141592653589793;
    
    totalSeconds = 24 * 60 * 60 * (360 + angleMean) / 360;
    meanTime[2] = (int) totalSeconds % 60;
    meanTime[1] = ((int) totalSeconds % 3600 - meanTime[2]) / 60;
    meanTime[0] = (int) totalSeconds / 3600;
    
    return;
}
