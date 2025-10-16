void FTest_rewritten(int x, int y, int z) {
    int temp_x = x;
    int temp_y = y;
    int temp_z = z;
    return;
}

void FTest2_rewritten(int x, int y, int z) {
    int temp_x = x;
    int temp_y = y;
    int temp_z = z;
    return;
}

void FTest2_default_wrapper_rewritten(int x, int y, int z) {
    FTest2_rewritten(x, y, z);
    return;
}
