int foo_bar_baz(int n1, int n2) {
    int ctx[5];
    int exs[5][2];
    char what[5][128];
    ctx[0] = 5;
    ctx[1] = -1;
    
    if (n1 == 0) {
        if (ctx[1] + 1 == ctx[0]) {
            ctx[1] = ctx[1] - 1;
        } else {
            ctx[1] = ctx[1] + 1;
        }
        exs[ctx[1]][0] = 10;
        for (int i = 0; i < 128; i = i + 1) {
            what[ctx[1]][i] = "U0 Drink Error. Insufficient drinks in bar Baz."[i];
            if ("U0 Drink Error. Insufficient drinks in bar Baz."[i] == 0) {
                break;
            }
        }
    } else {
        if (ctx[1] + 1 == ctx[0]) {
            ctx[1] = ctx[1] - 1;
        } else {
            ctx[1] = ctx[1] + 1;
        }
        exs[ctx[1]][0] = 11;
        for (int i = 0; i < 128; i = i + 1) {
            what[ctx[1]][i] = "U1 Bartender Error. Bartender kicked customer out of bar Baz."[i];
            if ("U1 Bartender Error. Bartender kicked customer out of bar Baz."[i] == 0) {
                break;
            }
        }
    }
    
    for (int j = 0; j < 5; j = j + 1) {
        if (ctx[1] >= 0 && exs[ctx[1]][0] == 10) {
            if (ctx[1] >= 0) {
                ctx[1] = ctx[1] - 1;
            }
        }
    }
    
    if (ctx[1] >= 0) {
        return -1;
    }
    
    if (n2 == 0) {
        if (ctx[1] + 1 == ctx[0]) {
            ctx[1] = ctx[1] - 1;
        } else {
            ctx[1] = ctx[1] + 1;
        }
        exs[ctx[1]][0] = 10;
        for (int i = 0; i < 128; i = i + 1) {
            what[ctx[1]][i] = "U0 Drink Error. Insufficient drinks in bar Baz."[i];
            if ("U0 Drink Error. Insufficient drinks in bar Baz."[i] == 0) {
                break;
            }
        }
    } else {
        if (ctx[1] + 1 == ctx[0]) {
            ctx[1] = ctx[1] - 1;
        } else {
            ctx[1] = ctx[1] + 1;
        }
        exs[ctx[1]][0] = 11;
        for (int i = 0; i < 128; i = i + 1) {
            what[ctx[1]][i] = "U1 Bartender Error. Bartender kicked customer out of bar Baz."[i];
            if ("U1 Bartender Error. Bartender kicked customer out of bar Baz."[i] == 0) {
                break;
            }
        }
    }
    
    for (int j = 0; j < 5; j = j + 1) {
        if (ctx[1] >= 0 && exs[ctx[1]][0] == 10) {
            if (ctx[1] >= 0) {
                ctx[1] = ctx[1] - 1;
            }
        }
    }
    
    return -1;
}
