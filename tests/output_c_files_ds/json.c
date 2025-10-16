void serialize_value(int gen, int val, int parse_numbers) {
    int type;
    int i;
    int len;
    int string_len;
    int object_len;
    int array_len;
    
    type = val;
    if (type == 1) {
        string_len = 0;
        for (i = 0; val != 0; i = i + 1) {
            string_len = string_len + 1;
        }
    }
    else if (type == 2) {
        if (parse_numbers != 0 && (val & 1) != 0) {
        }
        else if (parse_numbers != 0 && (val & 2) != 0) {
        }
        else {
            len = 0;
            for (i = 0; val != 0; i = i + 1) {
                len = len + 1;
            }
        }
    }
    else if (type == 3) {
        object_len = 0;
        for (i = 0; i < object_len; i = i + 1) {
            string_len = 0;
            for (int j = 0; val != 0; j = j + 1) {
                string_len = string_len + 1;
            }
            serialize_value(gen, val, parse_numbers);
        }
    }
    else if (type == 4) {
        array_len = 0;
        for (i = 0; i < array_len; i = i + 1) {
            serialize_value(gen, val, parse_numbers);
        }
    }
    else if (type == 5) {
    }
    else if (type == 6) {
    }
    else if (type == 7) {
    }
    else {
    }
    return;
}
