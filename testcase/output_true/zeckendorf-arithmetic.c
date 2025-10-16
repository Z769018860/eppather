int inv(int a) {
    return a ^ -1;
}

void zeckendorf_operations(int self_dVal, int self_dLen, int rhs_dVal, int rhs_dLen, int operation) {
    int i;
    int j;
    int pos;
    int gn;
    int nr_dVal = 0;
    int nr_dLen = 0;
    int na_dVal = rhs_dVal;
    int na_dLen = rhs_dLen;
    int nb_dVal = rhs_dVal;
    int nb_dLen = rhs_dLen;
    int nt_dVal;
    int nt_dLen;
    
    if (operation == 0) {
        self_dVal = self_dVal + 1;
        for (i = 0; i < 5; i = i + 1) {
            if (self_dLen < i) {
                self_dLen = i;
            }
            j = (self_dVal >> (i * 2)) & 3;
            if (j == 0 || j == 1) {
                break;
            }
            if (j == 2) {
                if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                    break;
                }
                self_dVal = self_dVal + (1 << (i * 2 + 1));
                break;
            }
            if (j == 3) {
                self_dVal = self_dVal & inv(3 << (i * 2));
                pos = (i + 1) * 2;
                if (pos == 0) {
                    self_dVal = self_dVal + 1;
                    for (i = 0; i < 5; i = i + 1) {
                        if (self_dLen < i) {
                            self_dLen = i;
                        }
                        j = (self_dVal >> (i * 2)) & 3;
                        if (j == 0 || j == 1) {
                            break;
                        }
                        if (j == 2) {
                            if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                break;
                            }
                            self_dVal = self_dVal + (1 << (i * 2 + 1));
                            break;
                        }
                        if (j == 3) {
                            self_dVal = self_dVal & inv(3 << (i * 2));
                            pos = (i + 1) * 2;
                        }
                    }
                }
                if (((self_dVal >> pos) & 1) == 0) {
                    self_dVal = self_dVal + (1 << pos);
                    for (i = 0; i < 5; i = i + 1) {
                        if (self_dLen < i) {
                            self_dLen = i;
                        }
                        j = (self_dVal >> (i * 2)) & 3;
                        if (j == 0 || j == 1) {
                            break;
                        }
                        if (j == 2) {
                            if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                break;
                            }
                            self_dVal = self_dVal + (1 << (i * 2 + 1));
                            break;
                        }
                        if (j == 3) {
                            self_dVal = self_dVal & inv(3 << (i * 2));
                            pos = (i + 1) * 2;
                        }
                    }
                    if (pos > 1) {
                        for (i = 0; i < 5; i = i + 1) {
                            if (self_dLen < i) {
                                self_dLen = i;
                            }
                            j = (self_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                self_dVal = self_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                self_dVal = self_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                    }
                } else {
                    self_dVal = self_dVal & inv(1 << pos);
                    pos = pos + 1;
                    if (pos == 0) {
                        self_dVal = self_dVal + 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (self_dLen < i) {
                                self_dLen = i;
                            }
                            j = (self_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                self_dVal = self_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                self_dVal = self_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                    }
                    pos = pos - (pos > 1 ? 2 : 1);
                    if (pos == 0) {
                        self_dVal = self_dVal + 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (self_dLen < i) {
                                self_dLen = i;
                            }
                            j = (self_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                self_dVal = self_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                self_dVal = self_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                    }
                }
            }
        }
    } else if (operation == 1) {
        for (gn = 0; gn < 5; gn = gn + 1) {
            if (((rhs_dVal >> gn) & 1) == 1) {
                pos = gn;
                if (pos == 0) {
                    self_dVal = self_dVal + 1;
                    for (i = 0; i < 5; i = i + 1) {
                        if (self_dLen < i) {
                            self_dLen = i;
                        }
                        j = (self_dVal >> (i * 2)) & 3;
                        if (j == 0 || j == 1) {
                            break;
                        }
                        if (j == 2) {
                            if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                break;
                            }
                            self_dVal = self_dVal + (1 << (i * 2 + 1));
                            break;
                        }
                        if (j == 3) {
                            self_dVal = self_dVal & inv(3 << (i * 2));
                            pos = (i + 1) * 2;
                        }
                    }
                }
                if (((self_dVal >> pos) & 1) == 0) {
                    self_dVal = self_dVal + (1 << pos);
                    for (i = 0; i < 5; i = i + 1) {
                        if (self_dLen < i) {
                            self_dLen = i;
                        }
                        j = (self_dVal >> (i * 2)) & 3;
                        if (j == 0 || j == 1) {
                            break;
                        }
                        if (j == 2) {
                            if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                break;
                            }
                            self_dVal = self_dVal + (1 << (i * 2 + 1));
                            break;
                        }
                        if (j == 3) {
                            self_dVal = self_dVal & inv(3 << (i * 2));
                            pos = (i + 1) * 2;
                        }
                    }
                    if (pos > 1) {
                        for (i = 0; i < 5; i = i + 1) {
                            if (self_dLen < i) {
                                self_dLen = i;
                            }
                            j = (self_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                self_dVal = self_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                self_dVal = self_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                    }
                } else {
                    self_dVal = self_dVal & inv(1 << pos);
                    pos = pos + 1;
                    if (pos == 0) {
                        self_dVal = self_dVal + 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (self_dLen < i) {
                                self_dLen = i;
                            }
                            j = (self_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                self_dVal = self_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                self_dVal = self_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                    }
                    pos = pos - (pos > 1 ? 2 : 1);
                    if (pos == 0) {
                        self_dVal = self_dVal + 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (self_dLen < i) {
                                self_dLen = i;
                            }
                            j = (self_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                self_dVal = self_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                self_dVal = self_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                    }
                }
            }
        }
    } else if (operation == 2) {
        for (gn = 0; gn < 5; gn = gn + 1) {
            if (((rhs_dVal >> gn) & 1) == 1) {
                pos = gn;
                if (((self_dVal >> pos) & 1) == 1) {
                    self_dVal = self_dVal & inv(1 << pos);
                } else {
                    pos = pos + 1;
                    if (pos == 0) {
                        self_dVal = self_dVal + 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (self_dLen < i) {
                                self_dLen = i;
                            }
                            j = (self_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                self_dVal = self_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                self_dVal = self_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                    }
                    if (pos > 0) {
                        pos = pos - 1;
                        if (pos == 0) {
                            self_dVal = self_dVal + 1;
                            for (i = 0; i < 5; i = i + 1) {
                                if (self_dLen < i) {
                                    self_dLen = i;
                                }
                                j = (self_dVal >> (i * 2)) & 3;
                                if (j == 0 || j == 1) {
                                    break;
                                }
                                if (j == 2) {
                                    if (((self_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                        break;
                                    }
                                    self_dVal = self_dVal + (1 << (i * 2 + 1));
                                    break;
                                }
                                if (j == 3) {
                                    self_dVal = self_dVal & inv(3 << (i * 2));
                                    pos = (i + 1) * 2;
                                }
                            }
                        }
                    }
                }
            }
        }
        while ((((self_dVal >> self_dLen * 2) & 3) == 0) || (self_dLen == 0)) {
            self_dLen = self_dLen - 1;
        }
    } else if (operation == 3) {
        for (i = 0; i < 5; i = i + 1) {
            if (((self_dVal >> i) & 1) > 0) {
                for (gn = 0; gn < 5; gn = gn + 1) {
                    if (((nb_dVal >> gn) & 1) == 1) {
                        pos = gn;
                        if (pos == 0) {
                            nr_dVal = nr_dVal + 1;
                            for (i = 0; i < 5; i = i + 1) {
                                if (nr_dLen < i) {
                                    nr_dLen = i;
                                }
                                j = (nr_dVal >> (i * 2)) & 3;
                                if (j == 0 || j == 1) {
                                    break;
                                }
                                if (j == 2) {
                                    if (((nr_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                        break;
                                    }
                                    nr_dVal = nr_dVal + (1 << (i * 2 + 1));
                                    break;
                                }
                                if (j == 3) {
                                    nr_dVal = nr_dVal & inv(3 << (i * 2));
                                    pos = (i + 1) * 2;
                                }
                            }
                        }
                        if (((nr_dVal >> pos) & 1) == 0) {
                            nr_dVal = nr_dVal + (1 << pos);
                            for (i = 0; i < 5; i = i + 1) {
                                if (nr_dLen < i) {
                                    nr_dLen = i;
                                }
                                j = (nr_dVal >> (i * 2)) & 3;
                                if (j == 0 || j == 1) {
                                    break;
                                }
                                if (j == 2) {
                                    if (((nr_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                        break;
                                    }
                                    nr_dVal = nr_dVal + (1 << (i * 2 + 1));
                                    break;
                                }
                                if (j == 3) {
                                    nr_dVal = nr_dVal & inv(3 << (i * 2));
                                    pos = (i + 1) * 2;
                                }
                            }
                            if (pos > 1) {
                                for (i = 0; i < 5; i = i + 1) {
                                    if (nr_dLen < i) {
                                        nr_dLen = i;
                                    }
                                    j = (nr_dVal >> (i * 2)) & 3;
                                    if (j == 0 || j == 1) {
                                        break;
                                    }
                                    if (j == 2) {
                                        if (((nr_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                            break;
                                        }
                                        nr_dVal = nr_dVal + (1 << (i * 2 + 1));
                                        break;
                                    }
                                    if (j == 3) {
                                        nr_dVal = nr_dVal & inv(3 << (i * 2));
                                        pos = (i + 1) * 2;
                                    }
                                }
                            }
                        } else {
                            nr_dVal = nr_dVal & inv(1 << pos);
                            pos = pos + 1;
                            if (pos == 0) {
                                nr_dVal = nr_dVal + 1;
                                for (i = 0; i < 5; i = i + 1) {
                                    if (nr_dLen < i) {
                                        nr_dLen = i;
                                    }
                                    j = (nr_dVal >> (i * 2)) & 3;
                                    if (j == 0 || j == 1) {
                                        break;
                                    }
                                    if (j == 2) {
                                        if (((nr_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                            break;
                                        }
                                        nr_dVal = nr_dVal + (1 << (i * 2 + 1));
                                        break;
                                    }
                                    if (j == 3) {
                                        nr_dVal = nr_dVal & inv(3 << (i * 2));
                                        pos = (i + 1) * 2;
                                    }
                                }
                            }
                            pos = pos - (pos > 1 ? 2 : 1);
                            if (pos == 0) {
                                nr_dVal = nr_dVal + 1;
                                for (i = 0; i < 5; i = i + 1) {
                                    if (nr_dLen < i) {
                                        nr_dLen = i;
                                    }
                                    j = (nr_dVal >> (i * 2)) & 3;
                                    if (j == 0 || j == 1) {
                                        break;
                                    }
                                    if (j == 2) {
                                        if (((nr_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                            break;
                                        }
                                        nr_dVal = nr_dVal + (1 << (i * 2 + 1));
                                        break;
                                    }
                                    if (j == 3) {
                                        nr_dVal = nr_dVal & inv(3 << (i * 2));
                                        pos = (i + 1) * 2;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            nt_dVal = nb_dVal;
            nt_dLen = nb_dLen;
            for (gn = 0; gn < 5; gn = gn + 1) {
                if (((na_dVal >> gn) & 1) == 1) {
                    pos = gn;
                    if (pos == 0) {
                        nb_dVal = nb_dVal + 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (nb_dLen < i) {
                                nb_dLen = i;
                            }
                            j = (nb_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((nb_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                nb_dVal = nb_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                nb_dVal = nb_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                    }
                    if (((nb_dVal >> pos) & 1) == 0) {
                        nb_dVal = nb_dVal + (1 << pos);
                        for (i = 0; i < 5; i = i + 1) {
                            if (nb_dLen < i) {
                                nb_dLen = i;
                            }
                            j = (nb_dVal >> (i * 2)) & 3;
                            if (j == 0 || j == 1) {
                                break;
                            }
                            if (j == 2) {
                                if (((nb_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                    break;
                                }
                                nb_dVal = nb_dVal + (1 << (i * 2 + 1));
                                break;
                            }
                            if (j == 3) {
                                nb_dVal = nb_dVal & inv(3 << (i * 2));
                                pos = (i + 1) * 2;
                            }
                        }
                        if (pos > 1) {
                            for (i = 0; i < 5; i = i + 1) {
                                if (nb_dLen < i) {
                                    nb_dLen = i;
                                }
                                j = (nb_dVal >> (i * 2)) & 3;
                                if (j == 0 || j == 1) {
                                    break;
                                }
                                if (j == 2) {
                                    if (((nb_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                        break;
                                    }
                                    nb_dVal = nb_dVal + (1 << (i * 2 + 1));
                                    break;
                                    }
                                if (j == 3) {
                                    nb_dVal = nb_dVal & inv(3 << (i * 2));
                                    pos = (i + 1) * 2;
                                }
                            }
                        }
                    } else {
                        nb_dVal = nb_dVal & inv(1 << pos);
                        pos = pos + 1;
                        if (pos == 0) {
                            nb_dVal = nb_dVal + 1;
                            for (i = 0; i < 5; i = i + 1) {
                                if (nb_dLen < i) {
                                    nb_dLen = i;
                                }
                                j = (nb_dVal >> (i * 2)) & 3;
                                if (j == 0 || j == 1) {
                                    break;
                                }
                                if (j == 2) {
                                    if (((nb_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                        break;
                                    }
                                    nb_dVal = nb_dVal + (1 << (i * 2 + 1));
                                    break;
                                }
                                if (j == 3) {
                                    nb_dVal = nb_dVal & inv(3 << (i * 2));
                                    pos = (i + 1) * 2;
                                }
                            }
                        }
                        pos = pos - (pos > 1 ? 2 : 1);
                        if (pos == 0) {
                            nb_dVal = nb_dVal + 1;
                            for (i = 0; i < 5; i = i + 1) {
                                if (nb_dLen < i) {
                                    nb_dLen = i;
                                }
                                j = (nb_dVal >> (i * 2)) & 3;
                                if (j == 0 || j == 1) {
                                    break;
                                }
                                if (j == 2) {
                                    if (((nb_dVal >> ((i + 1) * 2)) & 1) != 1) {
                                        break;
                                    }
                                    nb_dVal = nb_dVal + (1 << (i * 2 + 1));
                                    break;
                                }
                                if (j == 3) {
                                    nb_dVal = nb_dVal & inv(3 << (i * 2));
                                    pos = (i + 1) * 2;
                                }
                            }
                        }
                    }
                }
            }
            na_dVal = nt_dVal;
            na_dLen = nt_dLen;
        }
        self_dVal = nr_dVal;
        self_dLen = nr_dLen;
    }
    return;
}
