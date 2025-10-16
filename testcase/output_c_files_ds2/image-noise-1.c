void blit_noise(int surf_w, int surf_h, int surf_pixels[5]) {
    int i;
    int dim;
    int frames[5];
    int t_acc[5];
    int last_t[5];
    int t[5];
    int dt[5];
    int el_time[5];
    
    dim = surf_w * surf_h;
    frames[0] = 0;
    t_acc[0] = 0;
    last_t[0] = 0;
    
    for (;;) {
        for (i = 0; i < dim; i = i + 1) {
            surf_pixels[i] = ((rand() & 1) ? 255 : 0);
        }
        frames[0] = frames[0] + 1;
        
        t[0] = 0;
        dt[0] = t[0] - last_t[0];
        t_acc[0] = t_acc[0] + dt[0];
        if (t_acc[0] > 1000) {
            el_time[0] = t_acc[0] / 1000;
            t_acc[0] = 0;
            frames[0] = 0;
        }
        last_t[0] = t[0];
    }
    return;
}
