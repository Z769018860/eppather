void next_world(const char *in, char *out, int w, int h)
{
    int i;
    int n;
    n = w * h;
    
    for (i = 0; i < n; i = i + 1) {
        if (in[i] == ' ') {
            out[i] = ' ';
        } else {
            if (in[i] == 't') {
                out[i] = '.';
            } else {
                if (in[i] == 'H') {
                    out[i] = 't';
                } else {
                    if (in[i] == '.') {
                        int hc;
                        hc = 0;
                        if (in[i-w-1] == 'H') {
                            hc = hc + 1;
                        }
                        if (in[i-w] == 'H') {
                            hc = hc + 1;
                        }
                        if (in[i-w+1] == 'H') {
                            hc = hc + 1;
                        }
                        if (in[i-1] == 'H') {
                            hc = hc + 1;
                        }
                        if (in[i+1] == 'H') {
                            hc = hc + 1;
                        }
                        if (in[i+w-1] == 'H') {
                            hc = hc + 1;
                        }
                        if (in[i+w] == 'H') {
                            hc = hc + 1;
                        }
                        if (in[i+w+1] == 'H') {
                            hc = hc + 1;
                        }
                        if (hc == 1 || hc == 2) {
                            out[i] = 'H';
                        } else {
                            out[i] = '.';
                        }
                    } else {
                        out[i] = in[i];
                    }
                }
            }
        }
    }
    out[i] = in[i];
    return;
}
