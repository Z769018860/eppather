int configs_member_handler(int type, int data, int value, int v_len, int format, int *fullname, int *favouritefruit, int *needspeeling, int *seedsremoved, int *otherfamily, int *otherfamily_len, int *_configs_left) {
    if (type != 1) {
        return 0;
    }
    
    if (data == 1) {
        if (*fullname != 0) {
            return 0;
        }
        *fullname = value;
        *_configs_left = *_configs_left - 1;
    } else if (data == 2) {
        if (*favouritefruit != 0) {
            return 0;
        }
        *favouritefruit = value;
        *_configs_left = *_configs_left - 1;
    } else if (data == 3) {
        if ((*needspeeling & 0x80) == 0) {
            return 0;
        }
        *needspeeling = (value != 0);
        *_configs_left = *_configs_left - 1;
    } else if (data == 4) {
        if ((*seedsremoved & 0x80) == 0) {
            return 0;
        }
        *seedsremoved = (value != 0);
        *_configs_left = *_configs_left - 1;
    } else if (*otherfamily == 0 && data == 5) {
        if (*otherfamily != 0) {
            return 0;
        }
        *otherfamily = value;
        *otherfamily_len = v_len;
        *_configs_left = *_configs_left - 1;
    }
    
    return (*_configs_left == 0);
}

int populate_configs(int *fullname, int *favouritefruit, int *needspeeling, int *seedsremoved, int *otherfamily, int *otherfamily_len, int *_configs_left) {
    *fullname = 0;
    *favouritefruit = 0;
    *needspeeling = 0x80;
    *seedsremoved = 0x80;
    *otherfamily = 0;
    *otherfamily_len = 0;
    *_configs_left = 5;
    
    int result = 0;
    if (result != 0) {
        return 1;
    }
    
    *needspeeling = *needspeeling & 0x7F;
    *seedsremoved = *seedsremoved & 0x7F;
    
    return 0;
}

void main() {
    int fullname;
    int favouritefruit;
    int needspeeling;
    int seedsremoved;
    int otherfamily;
    int otherfamily_len;
    int _configs_left;
    
    if (populate_configs(&fullname, &favouritefruit, &needspeeling, &seedsremoved, &otherfamily, &otherfamily_len, &_configs_left) != 0) {
        return;
    }
    
    return;
}
