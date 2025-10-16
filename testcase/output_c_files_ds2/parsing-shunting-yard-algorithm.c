int parse(int prec_booster, int l_queue, int l_stack, int stack_len, int queue_len, char* s) {
    int stack[256][3];
    int queue[256][3];
    int m_so;
    int m_eo;
    int i;
    int j;
    int k;
    int t_prec;
    int t_assoc;
    int tok_prec;
    int tok_assoc;
    int p_prec;
    int p_assoc;
    int s_len;
    int s_index;
    int t_index;
    int p_index;
    int arg_match;
    int op_match;
    int paren_count;
    
    prec_booster = 0;
    l_queue = 0;
    l_stack = 0;
    paren_count = 0;
    s_index = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        arg_match = 0;
        op_match = 0;
        
        for (j = 0; j < 5; j = j + 1) {
            if (s[s_index] == ' ') {
                s_index = s_index + 1;
            }
            
            if (s[s_index] == '\0') {
                break;
            }
            
            if (s[s_index] == '(') {
                paren_count = paren_count + 1;
                prec_booster = prec_booster + 100;
                s_index = s_index + 1;
                continue;
            }
            
            if (s[s_index] == ')') {
                if (prec_booster < 100) {
                    return 0;
                }
                prec_booster = prec_booster - 100;
                paren_count = paren_count - 1;
                s_index = s_index + 1;
                continue;
            }
            
            if (s[s_index] >= '0' && s[s_index] <= '9') {
                m_so = s_index;
                while (s[s_index] >= '0' && s[s_index] <= '9') {
                    s_index = s_index + 1;
                }
                m_eo = s_index;
                queue[l_queue][0] = m_so;
                queue[l_queue][1] = m_eo - m_so;
                queue[l_queue][2] = 0;
                l_queue = l_queue + 1;
                arg_match = 1;
                break;
            }
            
            if (s[s_index] == '+' || s[s_index] == '-' || s[s_index] == '*' || s[s_index] == '/' || s[s_index] == '^') {
                m_so = s_index;
                s_index = s_index + 1;
                if (s[s_index] == '*' && s[s_index - 1] == '*') {
                    s_index = s_index + 1;
                    p_prec = 3;
                    p_assoc = 2;
                } else if (s[s_index - 1] == '^') {
                    p_prec = 3;
                    p_assoc = 2;
                } else if (s[s_index - 1] == '*' || s[s_index - 1] == '/') {
                    p_prec = 2;
                    p_assoc = 1;
                } else if (s[s_index - 1] == '+' || s[s_index - 1] == '-') {
                    p_prec = 1;
                    p_assoc = 1;
                }
                m_eo = s_index;
                tok_prec = p_prec;
                tok_assoc = p_assoc;
                
                if (p_prec > 0) {
                    tok_prec = p_prec + prec_booster;
                }
                
                for (k = l_stack - 1; k >= 0; k = k - 1) {
                    t_prec = stack[k][2];
                    t_assoc = stack[k][1];
                    if (!(t_prec == tok_prec && t_assoc == 1) && t_prec <= tok_prec) {
                        break;
                    }
                    queue[l_queue][0] = stack[k][0];
                    queue[l_queue][1] = stack[k][1];
                    queue[l_queue][2] = stack[k][2];
                    l_queue = l_queue + 1;
                    l_stack = l_stack - 1;
                }
                
                stack[l_stack][0] = m_so;
                stack[l_stack][1] = tok_assoc;
                stack[l_stack][2] = tok_prec;
                l_stack = l_stack + 1;
                op_match = 1;
                break;
            }
        }
        
        if (!arg_match && !op_match) {
            return 0;
        }
    }
    
    if (paren_count != 0) {
        return 0;
    }
    
    for (i = l_stack - 1; i >= 0; i = i - 1) {
        queue[l_queue][0] = stack[i][0];
        queue[l_queue][1] = stack[i][1];
        queue[l_queue][2] = stack[i][2];
        l_queue = l_queue + 1;
    }
    
    return 1;
}
