void if2(int firsttest, int secondtest, int bothtrue, int firsttrue, int secondtrue, int bothfalse) {
    int result[5];
    result[0] = 0;
    if (firsttest != 0) {
        result[0] = result[0] + 0;
    } else {
        result[0] = result[0] + 2;
    }
    if (secondtest != 0) {
        result[0] = result[0] + 0;
    } else {
        result[0] = result[0] + 1;
    }
    if (result[0] == 0) {
        bothtrue = bothtrue;
    } else {
        if (result[0] == 1) {
            firsttrue = firsttrue;
        } else {
            if (result[0] == 2) {
                secondtrue = secondtrue;
            } else {
                if (result[0] == 3) {
                    bothfalse = bothfalse;
                }
            }
        }
    }
    return;
}
