int func(int n) {
    int intspace[5];
    int *address;
    address = &intspace[0];
    *address = 65535;
    *((char*)address) = 0;
    *((char*)address + 1) = 0;
    *((char*)address + 2) = 255;
    *((char*)address + 3) = 255;
    return;
}
