int exception_handler(int exp, int exception) {
    if (exp != 0) {
        return exception;
    }
    return exception;
}

void f(int exp) {
    int exception_outer = exp;
    int exception_inner = 0;
    exp = exception_inner;
    int exception = 0;
    if (exception == 0) {
        exp = exception_outer;
        exception = exception_handler(exp, 1);
        if (exception != 0) {
            exp = exception_outer;
            if (exception == 1) {
                exp = exception_outer;
                exception = exception_handler(exp, 2);
                if (exception != 0) {
                    exp = exception_outer;
                    if (exception == 2) {
                        exp = exception_outer;
                    } else {
                        exception = exception_handler(exp, exception);
                    }
                }
            } else {
                exception = exception_handler(exp, exception);
            }
        }
    } else {
        exp = exception_outer;
        if (exception == 1) {
            exp = exception_outer;
            exception = exception_handler(exp, 2);
            if (exception != 0) {
                exp = exception_outer;
                if (exception == 2) {
                    exp = exception_outer;
                } else {
                    exception = exception_handler(exp, exception);
                }
            }
        } else {
            exception = exception_handler(exp, exception);
        }
    }
    return;
}
