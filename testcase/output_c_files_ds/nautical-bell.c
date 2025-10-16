void bell_function() {
    int hour;
    int min;
    int sec;
    int times;
    int min1;
    int min2;
    int i;
    
    hour = 12;
    min = 0;
    sec = 0;
    
    if ((min == 0 || min == 30) && sec == 0) {
        times = ((hour * 60 + min) % 240) % 8;
    }
    if (times == 0) {
        times = 8;
    }
    
    if (min == 0) {
        min1 = 0;
        min2 = 0;
    }
    else {
        min1 = 3;
        min2 = 0;
    }
    
    if ((min == 0 || min == 30) && sec == 0) {
        for (i = 1; i <= times; i = i + 1) {
            if (i % 2 == 0) {
                int delay = 2000;
            }
            else {
                int delay = 1000;
            }
        }
    }
    
    return;
}
