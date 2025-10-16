int checkHouses(int ha[5][5]) {
    int c_add[5];
    int c_or[5];
    int m_add[5];
    int m_or[5];
    int d_add[5];
    int d_or[5];
    int a_add[5];
    int a_or[5];
    int s_add[5];
    int s_or[5];
    for (int i = 0; i < 5; i = i + 1) {
        c_add[i] = 0;
        c_or[i] = 0;
        m_add[i] = 0;
        m_or[i] = 0;
        d_add[i] = 0;
        d_or[i] = 0;
        a_add[i] = 0;
        a_or[i] = 0;
        s_add[i] = 0;
        s_or[i] = 0;
    }

    if (ha[2][3] >= 0 && ha[2][3] != 2) {
        return 0;
    }

    if (ha[0][1] >= 0 && ha[0][1] != 4) {
        return 0;
    }

    for (int i = 0; i < 5; i = i + 1) {
        if (ha[i][0] >= 0) {
            c_add[0] = c_add[0] + (1 << ha[i][0]);
            c_or[0] = c_or[0] | (1 << ha[i][0]);
        }
        if (ha[i][1] >= 0) {
            m_add[0] = m_add[0] + (1 << ha[i][1]);
            m_or[0] = m_or[0] | (1 << ha[i][1]);
        }
        if (ha[i][2] >= 0) {
            d_add[0] = d_add[0] + (1 << ha[i][2]);
            d_or[0] = d_or[0] | (1 << ha[i][2]);
        }
        if (ha[i][3] >= 0) {
            a_add[0] = a_add[0] + (1 << ha[i][3]);
            a_or[0] = a_or[0] | (1 << ha[i][3]);
        }
        if (ha[i][4] >= 0) {
            s_add[0] = s_add[0] + (1 << ha[i][4]);
            s_or[0] = s_or[0] | (1 << ha[i][4]);
        }

        if ((ha[i][1] >= 0 && ha[i][0] >= 0) && ((ha[i][1] == 0 && ha[i][0] != 0) || (ha[i][1] != 0 && ha[i][0] == 0))) {
            return 0;
        }

        if ((ha[i][1] >= 0 && ha[i][3] >= 0) && ((ha[i][1] == 1 && ha[i][3] != 0) || (ha[i][1] != 1 && ha[i][3] == 0))) {
            return 0;
        }

        if ((ha[i][1] >= 0 && ha[i][2] >= 0) && ((ha[i][1] == 2 && ha[i][2] != 0) || (ha[i][1] != 2 && ha[i][2] == 0))) {
            return 0;
        }

        if ((i > 0 && ha[i][0] >= 0) && ((ha[i - 1][0] == 1 && ha[i][0] != 2) || (ha[i - 1][0] != 1 && ha[i][0] == 2))) {
            return 0;
        }

        if ((ha[i][0] >= 0 && ha[i][2] >= 0) && ((ha[i][0] == 1 && ha[i][2] != 1) || (ha[i][0] != 1 && ha[i][2] == 1))) {
            return 0;
        }

        if ((ha[i][4] >= 0 && ha[i][3] >= 0) && ((ha[i][4] == 0 && ha[i][3] != 1) || (ha[i][4] != 0 && ha[i][3] == 1))) {
            return 0;
        }

        if ((ha[i][4] >= 0 && ha[i][0] >= 0) && ((ha[i][4] == 1 && ha[i][0] != 3) || (ha[i][4] != 1 && ha[i][0] == 3))) {
            return 0;
        }

        if (ha[i][4] == 2) {
            if (i == 0 && ha[i + 1][3] >= 0 && ha[i + 1][3] != 2) {
                return 0;
            } else if (i == 4 && ha[i - 1][3] != 2) {
                return 0;
            } else if (ha[i + 1][3] >= 0 && ha[i + 1][3] != 2 && ha[i - 1][3] != 2) {
                return 0;
            }
        }

        if (ha[i][4] == 1) {
            if (i == 0 && ha[i + 1][3] >= 0 && ha[i + 1][3] != 3) {
                return 0;
            } else if (i == 4 && ha[i - 1][3] != 3) {
                return 0;
            } else if (ha[i + 1][3] >= 0 && ha[i + 1][3] != 3 && ha[i - 1][3] != 3) {
                return 0;
            }
        }

        if ((ha[i][4] >= 0 && ha[i][2] >= 0) && ((ha[i][4] == 3 && ha[i][2] != 3) || (ha[i][4] != 3 && ha[i][2] == 3))) {
            return 0;
        }

        if ((ha[i][1] >= 0 && ha[i][4] >= 0) && ((ha[i][1] == 3 && ha[i][4] != 4) || (ha[i][1] != 3 && ha[i][4] == 4))) {
            return 0;
        }

        if (ha[i][1] == 4 && ((i < 4 && ha[i + 1][0] >= 0 && ha[i + 1][0] != 4) || (i > 0 && ha[i - 1][0] != 4))) {
            return 0;
        }

        if (ha[i][4] == 2) {
            if (i == 0 && ha[i + 1][2] >= 0 && ha[i + 1][2] != 4) {
                return 0;
            } else if (i == 4 && ha[i - 1][2] != 4) {
                return 0;
            } else if (ha[i + 1][2] >= 0 && ha[i + 1][2] != 4 && ha[i - 1][2] != 4) {
                return 0;
            }
        }
    }

    if ((c_add[0] != c_or[0]) || (m_add[0] != m_or[0]) || (d_add[0] != d_or[0]) || (a_add[0] != a_or[0]) || (s_add[0] != s_or[0])) {
        return 0;
    }

    if ((c_add[0] != 31) || (m_add[0] != 31) || (d_add[0] != 31) || (a_add[0] != 31) || (s_add[0] != 31)) {
        return 1;
    }

    return 2;
}

int bruteFill(int ha[5][5], int hno, int attr) {
    int stat = checkHouses(ha);
    if ((stat == 2) || (stat == 0)) {
        return stat;
    }

    int hb[5][5];
    for (int i = 0; i < 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            hb[i][j] = ha[i][j];
        }
    }

    for (int i = 0; i < 5; i = i + 1) {
        hb[hno][attr] = i;
        stat = checkHouses(hb);
        if (stat != 0) {
            int nexthno;
            int nextattr;
            if (attr < 4) {
                nextattr = attr + 1;
                nexthno = hno;
            } else {
                nextattr = 0;
                nexthno = hno + 1;
            }

            stat = bruteFill(hb, nexthno, nextattr);
            if (stat != 0) {
                for (int i = 0; i < 5; i = i + 1) {
                    for (int j = 0; j < 5; j = j + 1) {
                        ha[i][j] = hb[i][j];
                    }
                }
                return stat;
            }
        }
    }

    return 0;
}

void printHouses(int ha[5][5]) {
    int color[5][5];
    int man[5][5];
    int drink[5][5];
    int animal[5][5];
    int smoke[5][5];
    for (int i = 0; i < 5; i = i + 1) {
        color[i][0] = 0;
        man[i][0] = 0;
        drink[i][0] = 0;
        animal[i][0] = 0;
        smoke[i][0] = 0;
    }

    for (int i = 0; i < 5; i = i + 1) {
        if (ha[i][0] >= 0) {
            color[i][0] = ha[i][0];
        } else {
            color[i][0] = -1;
        }
        if (ha[i][1] >= 0) {
            man[i][0] = ha[i][1];
        } else {
            man[i][0] = -1;
        }
        if (ha[i][2] >= 0) {
            drink[i][0] = ha[i][2];
        } else {
            drink[i][0] = -1;
        }
        if (ha[i][3] >= 0) {
            animal[i][0] = ha[i][3];
        } else {
            animal[i][0] = -1;
        }
        if (ha[i][4] >= 0) {
            smoke[i][0] = ha[i][4];
        } else {
            smoke[i][0] = -1;
        }
    }
    return;
}
