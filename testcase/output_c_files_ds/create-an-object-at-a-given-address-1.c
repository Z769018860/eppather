int func() {
    int intspace;
    int *address;
    char *byteptr;
    address = &intspace;
    *address = 65535;
    byteptr = (char*)address;
    *byteptr = 0x00;
    byteptr = byteptr + 1;
    *byteptr = 0x00;
    byteptr = byteptr + 1;
    *byteptr = 0xff;
    byteptr = byteptr + 1;
    *byteptr = 0xff;
    return;
}
