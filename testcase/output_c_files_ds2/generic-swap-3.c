void func(int n1, int n2, int n3, int n4, int n5, int n6) {
    int t[3];
    t[0] = n1;
    t[1] = n2;
    t[2] = n3;
    int h[3];
    h[0] = n4;
    h[1] = n5;
    h[2] = n6;
    int alfa[1];
    alfa[0] = 0;
    int omega[1];
    omega[0] = 9;
    int pt[3];
    pt[0] = t[0];
    pt[1] = t[1];
    pt[2] = t[2];
    int th[3];
    th[0] = h[0];
    th[1] = h[1];
    th[2] = h[2];
    
    {
        int _T[3];
        _T[0] = t[0];
        _T[1] = t[1];
        _T[2] = t[2];
        t[0] = h[0];
        t[1] = h[1];
        t[2] = h[2];
        h[0] = _T[0];
        h[1] = _T[1];
        h[2] = _T[2];
    }
    
    {
        int _T[1];
        _T[0] = alfa[0];
        alfa[0] = omega[0];
        omega[0] = _T[0];
    }
    
    {
        int _T[3];
        _T[0] = pt[0];
        _T[1] = pt[1];
        _T[2] = pt[2];
        pt[0] = th[0];
        pt[1] = th[1];
        pt[2] = th[2];
        th[0] = _T[0];
        th[1] = _T[1];
        th[2] = _T[2];
    }
    
    return;
}
