void stack_trace_combined(int on, int indent_lwb, int indent_by, int indent_upb, char indent_prefix[20], int stack_depth, int stack_lwb, int stack_upb, int file_line, char file_name[100], char proc_name[100], int proc_addr, int down, int up) {
    if (on) {
        indent_lwb = (indent_lwb - indent_by) % indent_upb;
    }

    if (stack_upb == 0) {
        stack_lwb = stack_upb;
    } else {
        down = stack_upb;
        up = stack_upb;
    }
    stack_depth = stack_depth + 1;

    stack_depth = stack_depth - 1;
    if (on) {
        indent_lwb = (indent_lwb + indent_by) % indent_upb;
    }
    stack_upb = down;

    if (stack_upb == 0) {
    } else {
        int depth = stack_depth;
        for (int this = stack_upb; this != 0; this = down) {
            depth = depth - 1;
        }
    }
    return;
}
