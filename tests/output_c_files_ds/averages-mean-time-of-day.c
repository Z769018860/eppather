int timeToDegreesAndMeanAngle(int hour, int minute, int second, int angles[5], int size) {
    int totalSeconds;
    int degrees;
    int y_part = 0;
    int x_part = 0;
    int i;
    int angleMean;
    int meanHour;
    int meanMinute;
    int meanSecond;

    totalSeconds = hour * 3600 + minute * 60 + second;
    degrees = (360 * totalSeconds) / 86400;

    for (i = 0; i < size; i = i + 1) {
        int angle = angles[i];
        int radian = angle * 314159265 / 180000000000;
        int cos_val = 1000000 - (radian * radian) / 2 + (radian * radian * radian * radian) / 24;
        int sin_val = radian - (radian * radian * radian) / 6 + (radian * radian * radian * radian * radian) / 120;
        x_part = x_part + cos_val;
        y_part = y_part + sin_val;
    }

    angleMean = (y_part * 180000000000) / (size * 314159265);
    totalSeconds = (angleMean * 86400) / 360;
    meanSecond = totalSeconds % 60;
    meanMinute = (totalSeconds % 3600 - meanSecond) / 60;
    meanHour = totalSeconds / 3600;

    return meanHour * 10000 + meanMinute * 100 + meanSecond;
}
