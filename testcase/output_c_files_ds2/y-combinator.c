int fac_fib(int mode, int n) {
    int result[5];
    int self[5];
    int temp1[5];
    int temp2[5];
    int i;
    
    if (mode == 0) {
        if (n > 1) {
            temp1[0] = n - 1;
            for (i = 0; i < 5; i = i + 1) {
                if (i == 0) {
                    if (temp1[0] > 1) {
                        temp2[0] = temp1[0] - 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (i == 0) {
                                if (temp2[0] > 1) {
                                    result[0] = temp2[0] * (temp2[0] - 1);
                                } else {
                                    result[0] = 1;
                                }
                            }
                        }
                        result[0] = temp1[0] * result[0];
                    } else {
                        result[0] = 1;
                    }
                }
            }
            result[0] = n * result[0];
        } else {
            result[0] = 1;
        }
    } else {
        if (n > 1) {
            temp1[0] = n - 1;
            for (i = 0; i < 5; i = i + 1) {
                if (i == 0) {
                    if (temp1[0] > 1) {
                        temp2[0] = temp1[0] - 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (i == 0) {
                                if (temp2[0] > 1) {
                                    self[0] = temp2[0] - 1;
                                    for (i = 0; i < 5; i = i + 1) {
                                        if (i == 0) {
                                            if (self[0] > 1) {
                                                result[0] = self[0] + (self[0] - 1);
                                            } else {
                                                result[0] = 1;
                                            }
                                        }
                                    }
                                    result[0] = temp2[0] + result[0];
                                } else {
                                    result[0] = 1;
                                }
                            }
                        }
                        result[0] = temp1[0] + result[0];
                    } else {
                        result[0] = 1;
                    }
                }
            }
            temp1[0] = n - 2;
            for (i = 0; i < 5; i = i + 1) {
                if (i == 0) {
                    if (temp1[0] > 1) {
                        temp2[0] = temp1[0] - 1;
                        for (i = 0; i < 5; i = i + 1) {
                            if (i == 0) {
                                if (temp2[0] > 1) {
                                    self[0] = temp2[0] - 1;
                                    for (i = 0; i < 5; i = i + 1) {
                                        if (i == 0) {
                                            if (self[0] > 1) {
                                                result[0] = self[0] + (self[0] - 1);
                                            } else {
                                                result[0] = 1;
                                            }
                                        }
                                    }
                                    result[0] = temp2[0] + result[0];
                                } else {
                                    result[0] = 1;
                                }
                            }
                        }
                        result[0] = temp1[0] + result[0];
                    } else {
                        result[0] = 1;
                    }
                }
            }
            result[0] = result[0] + result[0];
        } else {
            result[0] = 1;
        }
    }
    return result[0];
}
