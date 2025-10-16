int create_window(int argc, int argv[5]) {
    int key_press_callback[5];
    int glut_init_args[5];
    int window_title[5];
    int keyboard_func[5];
    int main_loop[5];

    for (int i = 0; i < 5; i = i + 1) {
        glut_init_args[i] = 0;
        window_title[i] = 0;
        keyboard_func[i] = 0;
        main_loop[i] = 0;
    }

    for (int i = 0; i < 5; i = i + 1) {
        key_press_callback[i] = 0;
    }

    return;
}
