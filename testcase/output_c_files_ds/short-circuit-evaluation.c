int a(int in) {
    return in;
}

int b(int in) {
    return in;
}

void test() {
    int x;
    int temp_a;
    int temp_b;
    
    temp_a = a(0);
    if (temp_a != 0) {
        temp_b = b(1);
        x = temp_a && temp_b;
    } else {
        x = 0;
    }
    
    temp_a = a(1);
    if (temp_a == 0) {
        temp_b = b(0);
        x = temp_a || temp_b;
    } else {
        x = 1;
    }
    
    temp_a = a(1);
    if (temp_a != 0) {
        temp_b = b(0);
        x = temp_a && temp_b;
    } else {
        x = 0;
    }
    
    temp_a = a(0);
    if (temp_a == 0) {
        temp_b = b(0);
        x = temp_a || temp_b;
    } else {
        x = 1;
    }
    
    return;
}
