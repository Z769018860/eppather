void talk(int n1, int n2, int n3, int n4, int n5)
{
    int pid[5];
    int status[5];
    
    pid[0] = 0;
    status[0] = 0;
    
    for (n1 = 0; n1 < 5; n1 = n1 + 1) {
        if (pid[0] < 0) {
            break;
        }
    }
    
    for (n2 = 0; n2 < 5; n2 = n2 + 1) {
        if (pid[0] == 0) {
            break;
        }
    }
    
    for (n3 = 0; n3 < 5; n3 = n3 + 1) {
        if (!(status[0] == 0) || status[0] != 0) {
            break;
        }
    }
    
    return;
}
