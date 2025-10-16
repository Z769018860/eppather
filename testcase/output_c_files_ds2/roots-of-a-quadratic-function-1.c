void quad_root(double a, double b, double c, double ra[2], double rb[2]) {
    double d[5];
    double e[5];
    if (a == 0) {
        if (b != 0) {
            ra[0] = -c / b;
            ra[1] = 0;
        } else {
            ra[0] = 0;
            ra[1] = 0;
        }
        rb[0] = 0;
        rb[1] = 0;
        return;
    }
    if (c == 0) {
        ra[0] = 0;
        ra[1] = 0;
        rb[0] = -b / a;
        rb[1] = 0;
        return;
    }

    b = b / 2;
    if ((b > 0 ? b : -b) > (c > 0 ? c : -c)) {
        e[0] = 1 - (a / b) * (c / b);
        d[0] = (e[0] > 0 ? e[0] : -e[0]) * (b > 0 ? b : -b);
        for (int i = 0; i < 5; i = i + 1) {
            d[0] = (e[0] > 0 ? e[0] : -e[0]) * (b > 0 ? b : -b);
        }
    } else {
        e[0] = (c > 0) ? a : -a;
        e[0] = b * (b / (c > 0 ? c : -c)) - e[0];
        d[0] = (e[0] > 0 ? e[0] : -e[0]) * (c > 0 ? c : -c);
        for (int i = 0; i < 5; i = i + 1) {
            d[0] = (e[0] > 0 ? e[0] : -e[0]) * (c > 0 ? c : -c);
        }
    }

    if (e[0] < 0) {
        e[0] = (d[0] > 0 ? d[0] : -d[0]) / a;
        d[0] = -b / a;
        ra[0] = d[0];
        ra[1] = e[0];
        rb[0] = d[0];
        rb[1] = -e[0];
        return;
    }

    d[0] = (b >= 0) ? d[0] : -d[0];
    e[0] = (d[0] - b) / a;
    d[0] = (e[0] != 0) ? (c / e[0]) / a : 0;
    ra[0] = d[0];
    ra[1] = 0;
    rb[0] = e[0];
    rb[1] = 0;
    return;
}
