int stack[256];
int depth;

void rpn(char* s) {
    int a;
    int b;
    int i;
    int j;
    int k;
    int len;
    int is_num;
    int num;
    int sign;
    int digit;
    
    len = 0;
    while (s[len] != 0) {
        len = len + 1;
    }
    
    for (i = 0; i < len; i = i + 1) {
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || s[i] == '\f') {
            continue;
        }
        
        is_num = 1;
        num = 0;
        sign = 1;
        j = i;
        if (s[j] == '-') {
            sign = -1;
            j = j + 1;
        }
        
        for (k = j; k < len; k = k + 1) {
            if (s[k] >= '0' && s[k] <= '9') {
                digit = s[k] - '0';
                num = num * 10 + digit;
            } else {
                break;
            }
        }
        
        if (k > j) {
            num = num * sign;
            i = k - 1;
            if (depth >= 256) {
                return;
            }
            stack[depth] = num;
            depth = depth + 1;
            continue;
        }
        
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') {
            if (depth < 1) {
                return;
            }
            depth = depth - 1;
            b = stack[depth];
            if (depth < 1) {
                return;
            }
            depth = depth - 1;
            a = stack[depth];
            
            if (s[i] == '+') {
                a = a + b;
            } else if (s[i] == '-') {
                a = a - b;
            } else if (s[i] == '*') {
                a = a * b;
            } else if (s[i] == '/') {
                a = a / b;
            } else if (s[i] == '^') {
                num = 1;
                for (k = 0; k < b; k = k + 1) {
                    num = num * a;
                }
                a = num;
            }
            
            if (depth >= 256) {
                return;
            }
            stack[depth] = a;
            depth = depth + 1;
        } else {
            return;
        }
    }
    
    return;
}
