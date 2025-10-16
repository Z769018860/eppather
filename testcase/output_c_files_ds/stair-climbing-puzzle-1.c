void step_up(void) {
    for (; ; ) {
        int result;
        result = step();
        if (result != 0) {
            break;
        }
        step_up();
    }
    return;
}
