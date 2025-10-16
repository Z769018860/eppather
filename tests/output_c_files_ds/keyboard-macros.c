int process_key_events() {
    int event_type;
    int key_code;
    int key_pressed;
    int loop_flag;
    int f7_pressed;
    int f6_pressed;
    
    loop_flag = 1;
    f7_pressed = 0;
    f6_pressed = 0;
    
    for (; loop_flag != 0; ) {
        event_type = 0;
        key_code = 0;
        key_pressed = 0;
        
        if (event_type == 2) {
            if (key_code == 1) {
                f7_pressed = 1;
            } else {
                if (key_code == 2) {
                    f6_pressed = 1;
                    loop_flag = 0;
                }
            }
        }
    }
    
    return;
}
