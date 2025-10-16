int configs_member_handler(int type, int data, int value, int v_len, int format, int fullname, int favouritefruit, int needspeeling, int seedsremoved, int otherfamily, int otherfamily_len, int configs_left) {
    int result[5];
    result[0] = 0;
    if (type != 1) {
        return result[0];
    }
    if (data == 1) {
        if (fullname != 0) {
            return result[0];
        }
        v_len = 5;
        fullname = value;
        configs_left = configs_left - 1;
    } else if (data == 2) {
        if (favouritefruit != 0) {
            return result[0];
        }
        v_len = 5;
        favouritefruit = value;
        configs_left = configs_left - 1;
    } else if (data == 3) {
        if ((needspeeling & 128) == 0) {
            return result[0];
        }
        needspeeling = 1;
        configs_left = configs_left - 1;
    } else if (data == 4) {
        if ((seedsremoved & 128) == 0) {
            return result[0];
        }
        seedsremoved = 1;
        configs_left = configs_left - 1;
    } else if (otherfamily == 0 && data == 5) {
        if (otherfamily != 0) {
            return result[0];
        }
        v_len = 5;
        otherfamily_len = 5;
        otherfamily = value;
        configs_left = configs_left - 1;
    }
    result[0] = (configs_left == 0) ? 1 : 0;
    return result[0];
}
