int solve_puzzle(void) {
    int house[5][5] = {0};
    int nationality[5] = {0};
    int pet[5] = {0};
    int drink[5] = {0};
    int smoke[5] = {0};
    int color[5] = {0};
    
    house[0][0] = 5;
    house[2][3] = 4;
    house[1][0] = 3;
    
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (house[i][0] == 5 && house[i][4] == 1) {
                color[i] = 1;
            }
            if (house[i][0] == 2 && house[i][1] == 2) {
                pet[i] = 2;
            }
            if (house[i][0] == 3 && house[i][2] == 3) {
                drink[i] = 3;
            }
            if (house[i][4] == 2 && house[i + 1][4] == 5) {
                color[i] = 2;
                color[i + 1] = 5;
            }
            if (house[i][2] == 5 && house[i][4] == 2) {
                drink[i] = 5;
                color[i] = 2;
            }
            if (house[i][3] == 5 && house[i][1] == 1) {
                smoke[i] = 5;
                pet[i] = 1;
            }
            if (house[i][4] == 3 && house[i][3] == 1) {
                color[i] = 3;
                smoke[i] = 1;
            }
            if (house[2][2] == 4) {
                drink[2] = 4;
            }
            if (house[0][0] == 4) {
                nationality[0] = 4;
            }
            if ((house[i][3] == 3 && house[i - 1][1] == 3) || (house[i][3] == 3 && house[i + 1][1] == 3)) {
                smoke[i] = 3;
                pet[i - 1] = 3;
                pet[i + 1] = 3;
            }
            if ((house[i][1] == 4 && house[i - 1][3] == 1) || (house[i][1] == 4 && house[i + 1][3] == 1)) {
                pet[i] = 4;
                smoke[i - 1] = 1;
                smoke[i + 1] = 1;
            }
            if (house[i][3] == 2 && house[i][2] == 2) {
                smoke[i] = 2;
                drink[i] = 2;
            }
            if (house[i][0] == 1 && house[i][3] == 4) {
                nationality[i] = 1;
                smoke[i] = 4;
            }
            if ((house[i][0] == 4 && house[i - 1][4] == 4) || (house[i][0] == 4 && house[i + 1][4] == 4)) {
                nationality[i] = 4;
                color[i - 1] = 4;
                color[i + 1] = 4;
            }
            if ((house[i][2] == 1 && house[i - 1][3] == 3) || (house[i][2] == 1 && house[i + 1][3] == 3)) {
                drink[i] = 1;
                smoke[i - 1] = 3;
                smoke[i + 1] = 3;
            }
        }
    }
    return;
}
