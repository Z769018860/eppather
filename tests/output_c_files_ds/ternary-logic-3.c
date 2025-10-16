int func() {
    int roses_are_red = 25;
    int violets_are_blue = 100;
    int i;
    int j;
    int result;
    int temp;
    int temp2;
    
    for (i = 0; i < 40; i = i + 1) {
        temp = 100 - roses_are_red;
        if (temp * 32767 > rand()) {
            result = 1;
        } else {
            result = 0;
        }
    }
    
    for (i = 0; i < 40; i = i + 1) {
        temp = roses_are_red * violets_are_blue / 100;
        if (temp * 32767 > rand()) {
            result = 1;
        } else {
            result = 0;
        }
    }
    
    for (i = 0; i < 40; i = i + 1) {
        temp = roses_are_red + violets_are_blue - roses_are_red * violets_are_blue / 100;
        if (temp * 32767 > rand()) {
            result = 1;
        } else {
            result = 0;
        }
    }
    
    for (i = 0; i < 40; i = i + 1) {
        temp = 100 - roses_are_red - roses_are_red + 2 * roses_are_red * roses_are_red / 100;
        if (temp * 32767 > rand()) {
            result = 1;
        } else {
            result = 0;
        }
    }
    
    return;
}
