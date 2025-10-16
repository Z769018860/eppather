void toggle_port() {
    int port_a[1];
    int dat;
    int addr;
    
    port_a[0] = port_a[0] ^ 0x01;
    dat = port_a[0];
    addr = 0x100;
    
    return;
}
