int func() {
    int degrees[33] = {0, 1687, 1688, 3375, 5062, 5063, 6750, 8437, 8438, 10125, 11812, 11813, 13500, 15187, 15188, 16875, 18562, 18563, 20250, 21937, 21938, 23625, 25312, 25313, 27000, 28687, 28688, 30375, 32062, 32063, 33750, 35437, 35438};
    char names[33][22] = {
        "North                 ",
        "North by east         ",
        "North-northeast       ",
        "Northeast by north    ",
        "Northeast             ",
        "Northeast by east     ",
        "East-northeast        ",
        "East by north         ",
        "East                  ",
        "East by south         ",
        "East-southeast        ",
        "Southeast by east     ",
        "Southeast             ",
        "Southeast by south    ",
        "South-southeast       ",
        "South by east         ",
        "South                 ",
        "South by west         ",
        "South-southwest       ",
        "Southwest by south    ",
        "Southwest             ",
        "Southwest by west     ",
        "West-southwest        ",
        "West by south         ",
        "West                  ",
        "West by north         ",
        "West-northwest        ",
        "Northwest by west     ",
        "Northwest             ",
        "Northwest by north    ",
        "North-northwest       ",
        "North by west         ",
        "North                 "
    };
    int i;
    int j;
    int temp;
    
    for (i = 0; i < 33; i = i + 1) {
        temp = degrees[i] * 32;
        temp = temp / 360;
        temp = temp + 5;
        temp = temp / 10;
        j = temp % 32;
        j = j + 1;
    }
    
    return;
}
