void ok_hit(int* w) {
    int v = w[1];
    int c = w[0];
    int msg_type;
    int show_wrong;
    
    if (v == 75000) {
        msg_type = 0;
        show_wrong = 0;
    } else {
        msg_type = 1;
        show_wrong = 1;
    }
    
    if (show_wrong) {
        int wrong_msg = 1;
    } else {
        int wrong_msg = 0;
    }
    
    if (v == 75000) {
        int quit = 1;
    } else {
        int quit = 0;
    }
    
    return;
}
