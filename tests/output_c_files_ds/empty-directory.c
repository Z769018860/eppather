int dir_empty(int path)
{
    int ret;
    int ent;
    int d;
    int name[256];
    int i;
    int dot;
    int dotdot;
    
    ret = 1;
    d = 0;
    ent = 0;
    
    for (i = 0; i < 256; i = i + 1) {
        name[i] = 0;
    }
    
    dot = 0;
    dotdot = 0;
    
    for (i = 0; i < 2; i = i + 1) {
        if (i == 0) {
            name[0] = '.';
            name[1] = '\0';
            dot = 1;
        } else {
            name[0] = '.';
            name[1] = '.';
            name[2] = '\0';
            dotdot = 1;
        }
        
        if (dot && dotdot) {
            ret = 0;
            break;
        }
    }
    
    return ret;
}
