void func(int port_addr) {
    int dat[5];
    int addr[5];
    int port_a[5];
    
    port_a[0] = port_addr;
    port_a[0] = port_a[0] ^ 1;
    dat[0] = port_a[0];
    addr[0] = port_a[0];
    
    return;
}
