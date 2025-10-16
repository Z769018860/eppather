int video_init(int width, int height, int bpp) {
    int result[5];
    result[0] = 0;
    int screen[5];
    screen[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1) {
        result[0] = result[0] + 1;
    }
    
    for (int j = 0; j < 5; j = j + 1) {
        screen[0] = screen[0] + 1;
    }
    
    return;
}
