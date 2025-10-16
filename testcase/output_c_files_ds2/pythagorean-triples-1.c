void pythagorean_triples(int max_p_param, int* pytha, int* prim) {
    int a[5];
    int b[5];
    int c[5];
    int t[5];
    int aa[5];
    int bb[5];
    int cc[5];
    int n[5];
    
    a[0] = 1;
    *pytha = 0;
    *prim = 0;
    
    for (; a[0] <= max_p_param / 3; a[0] = a[0] + 1) {
        aa[0] = a[0] * a[0];
        
        for (b[0] = a[0] + 1; b[0] < max_p_param / 2; b[0] = b[0] + 1) {
            bb[0] = b[0] * b[0];
            
            for (c[0] = b[0] + 1; c[0] < max_p_param / 2; c[0] = c[0] + 1) {
                cc[0] = c[0] * c[0];
                
                if (aa[0] + bb[0] < cc[0]) {
                    break;
                }
                if (a[0] + b[0] + c[0] > max_p_param) {
                    break;
                }
                
                if (aa[0] + bb[0] == cc[0]) {
                    *pytha = *pytha + 1;
                    
                    n[0] = b[0];
                    t[0] = a[0];
                    while (n[0]) {
                        t[1] = n[0];
                        n[0] = t[0] % n[0];
                        t[0] = t[1];
                    }
                    
                    if (t[0] == 1) {
                        *prim = *prim + 1;
                    }
                }
            }
        }
    }
    
    return;
}
