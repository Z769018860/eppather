int square(int env[2][2]) {
    int xbind[2];
    xbind[0] = env[0][0];
    xbind[1] = env[0][1];
    int xval = xbind[1];
    int result = xval * xval;
    return result;
}
