int func(int n) {
    int window[5];
    int argc[5];
    int argv[5];
    int gtk_init[5];
    int gtk_window_new[5];
    int gtk_window_set_title[5];
    int g_signal_connect[5];
    int gtk_widget_show_all[5];
    int gtk_main[5];
    int GTK_WINDOW_TOPLEVEL[5];
    int G_OBJECT[5];
    int gtk_main_quit[5];
    int NULL[5];
    
    gtk_init[0] = argc[0];
    gtk_init[1] = argv[0];
    
    window[0] = gtk_window_new[0];
    gtk_window_set_title[0] = window[0];
    gtk_window_set_title[1] = 0;
    
    g_signal_connect[0] = G_OBJECT[0];
    g_signal_connect[1] = window[0];
    g_signal_connect[2] = 0;
    g_signal_connect[3] = gtk_main_quit[0];
    g_signal_connect[4] = NULL[0];
    
    gtk_widget_show_all[0] = window[0];
    gtk_main[0] = 0;
    
    return;
}
