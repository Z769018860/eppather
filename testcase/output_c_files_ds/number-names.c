void say_number(const char *s) {
    int len = 0;
    int got_sign = 0;
    int i = 0;
    int n = 0;
    int r = 0;
    int has_lead = 0;
    int maxillion = 6;
    const char *end;
    
    while (s[len] != '\0') {
        len = len + 1;
    }
    
    i = 0;
    while (s[i] == ' ') {
        i = i + 1;
    }
    
    if (s[i] < '0' || s[i] > '9') {
        if (s[i] == '-') {
            got_sign = -1;
        } else if (s[i] == '+') {
            got_sign = 1;
        } else {
            return;
        }
        i = i + 1;
    } else {
        got_sign = 1;
    }
    
    while (s[i] == '0') {
        i = i + 1;
        if (s[i] == '\0') {
            return;
        }
    }
    
    len = 0;
    while (s[i + len] != '\0') {
        len = len + 1;
    }
    
    if (len == 0) {
        return;
    }
    
    for (i = 0; i < len; i = i + 1) {
        if (s[i] < '0' || s[i] > '9') {
            return;
        }
    }
    
    n = len / maxillion;
    r = len % maxillion;
    if (r == 0) {
        r = maxillion;
        n = n - 1;
    }
    
    end = s + len - n * maxillion;
    has_lead = 0;
    
    for (; n >= 0; n = n - 1) {
        int c[3];
        int j;
        int depth = n;
        int part_len = r;
        
        for (j = -3; j < 0; j = j + 1) {
            if (part_len + j >= 0) {
                c[j + 3] = s[part_len + j] - '0';
            } else {
                c[j + 3] = 0;
            }
        }
        
        if (c[0] + c[1] + c[2] != 0) {
            if (c[0] != 0) {
                has_lead = 1;
            }
            
            if (has_lead != 0 && (c[1] != 0 || c[2] != 0)) {
            }
            
            if (c[1] < 2) {
                if (c[1] != 0 || c[2] != 0) {
                }
            } else {
                if (c[1] != 0) {
                    if (c[2] != 0) {
                    }
                }
                if (c[2] != 0) {
                }
            }
            
            if (depth != 0) {
                has_lead = 1;
                if (depth == 0) {
                } else {
                }
            }
        }
        
        r = maxillion;
        s = end;
        end = end + r;
    }
    
    return;
}
