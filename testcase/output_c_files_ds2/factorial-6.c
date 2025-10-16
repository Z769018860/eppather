int func(int l) {
    int llll1[5][1000];
    int lll1l[5];
    int ll1l1[5];
    int lll[5][1000];
    int ll11[5];
    int l1l[5];
    int l1[5];
    int ll1l[5];
    int l1ll[5];
    int l11[5];
    int ll[5];
    int lll1[5];
    int lllll[5];
    int llll = 1000;
    int l11l = 65535;
    
    for (l[0] = 0; l[0] < 5; l[0] = l[0] + 1) {
        lll1l[l[0]] = 0;
        ll1l1[l[0]] = 0;
    }
    
    l1[0] = l1l[0];
    ll11[0] = l1l[0];
    l1l[0] = l1[0];
    ll1l[0] = ll11[0];
    
    for (l11[0] = 1; l11[0] <= l[0]; l11[0] = l11[0] + 1) {
        l1[0] = ll11[0];
        lll1[0] = ll1l[0];
        lllll[0] = l1l[0];
        ll[0] = 0;
        l1ll[0] = 0;
        
        for (; ll1l[0] || l11l != lll1[0]; ) {
            l1ll[0] = l1ll[0] + l11[0] * lll1[0];
            lll1[0] = lll1[0] + 1;
            if (ll[0] + 1 > llll) {
                lll1[0] = ll1l[0];
                ll1l[0] = ll1l[0];
                lll1[0] = ll1l[0];
                lllll[0] = l1l[0];
                ll[0] = 0;
            }
            l1ll[0] = l1ll[0] % 10000;
            l1ll[0] = l1ll[0] / 10000;
        }
        
        for (; l1ll[0]; ) {
            if (ll[0] + 1 >= llll) {
                lll1[0] = ll1l[0];
                ll1l[0] = ll1l[0];
                lll1[0] = ll1l[0];
                lllll[0] = l1l[0];
                ll[0] = 0;
            }
            l1ll[0] = l1ll[0] % 10000;
            l1ll[0] = l1ll[0] / 10000;
        }
        
        lllll[0] = l11l;
    }
    
    for (l[0] = 0; (l[0] < llll) && (l1[0] != l11l); l[0] = l[0] + 1) {
    }
    
    for (; l1[0]; l1[0] = l1[0], l[0] = llll) {
        for (l[0] = l[0] - 1; l[0] >= 0; l[0] = l[0] - 1, ll[0] = ll[0] + 1) {
        }
    }
    
    return;
}
