void quad_root(double a, double b, double c, double ra[2], double rb[2]) {
    double d;
    double e;
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
    if ((b < 0 ? -b : b) > (c < 0 ? -c : c)) {
        e = 1 - (a / b) * (c / b);
        d = (e < 0 ? -e : e) * (b < 0 ? -b : b);
        d = (d < 0 ? -d : d);
    } else {
        if (c > 0) {
            e = a;
        } else {
            e = -a;
        }
        e = b * (b / (c < 0 ? -c : c)) - e;
        d = (e < 0 ? -e : e) * (c < 0 ? -c : c);
        d = (d < 0 ? -d : d);
    }
    if (e < 0) {
        e = (d / a < 0 ? -d / a : d / a);
        d = -b / a;
        ra[0] = d;
        ra[1] = e;
        rb[0] = d;
        rb[1] = -e;
        return;
    }
    if (b >= 0) {
        d = d;
    } else {
        d = -d;
    }
    e = (d - b) / a;
    if (e != 0) {
        d = (c / e) / a;
    } else {
        d = 0;
    }
    ra[0] = d;
    ra[1] = 0;
    rb[0] = e;
    rb[1] = 0;
    return;
}
