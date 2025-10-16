void bell_function(int hour, int min, int sec) {
    int times[5];
    int min1[5];
    int min2[5];
    int i[5];
    int shortlag = 1000;
    int longlag = 2000;
    
    if ((min == 0 || min == 30) && sec == 0) {
        times[0] = ((hour * 60 + min) % 240) % 8;
    }
    if (times[0] == 0) {
        times[0] = 8;
    }
    
    if (min == 0) {
        min1[0] = 0;
        min2[0] = 0;
    } else {
        min1[0] = 3;
        min2[0] = 0;
    }
    
    if ((min == 0 || min == 30) && sec == 0) {
        for (i[0] = 1; i[0] <= times[0]; i[0] = i[0] + 1) {
            if (i[0] % 2 == 0) {
                for (i[1] = 0; i[1] < longlag; i[1] = i[1] + 1) {}
            } else {
                for (i[2] = 0; i[2] < shortlag; i[2] = i[2] + 1) {}
            }
        }
    }
    return;
}
