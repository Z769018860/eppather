void step_up(void) {
    int success[5];
    success[0] = step();
    if (success[0] == 0) {
        step_up();
        for (int i = 0; i < 5; i = i + 1) {
            success[0] = step();
            if (success[0] != 0) {
                break;
            }
        }
    }
    return;
}
