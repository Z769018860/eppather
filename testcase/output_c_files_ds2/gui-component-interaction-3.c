void gui_component_interaction(int IDC_INPUT, int IDC_INCREMENT, int IDC_RANDOM, int IDC_QUIT) {
    int dialog[5];
    dialog[0] = 0;
    dialog[1] = 0;
    dialog[2] = 154;
    dialog[3] = 46;
    
    int style[5];
    style[0] = 0x00000004 | 0x00000001 | 0x00000080 | 0x00000040 | 0x00C00000 | 0x10000000 | 0x00080000 | 0x00080000;
    
    int font[5];
    font[0] = 12;
    
    int controls[5][5];
    controls[0][0] = 7;
    controls[0][1] = 7;
    controls[0][2] = 140;
    controls[0][3] = 12;
    controls[0][4] = 0x00000080 | 0x00000001;
    
    controls[1][0] = 7;
    controls[1][1] = 25;
    controls[1][2] = 50;
    controls[1][3] = 14;
    
    controls[2][0] = 62;
    controls[2][1] = 25;
    controls[2][2] = 50;
    controls[2][3] = 14;
    
    controls[3][0] = 117;
    controls[3][1] = 25;
    controls[3][2] = 30;
    controls[3][3] = 14;
    
    return;
}
