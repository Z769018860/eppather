/* DeepSeek-generated summary, normalized for Eppather's bounded C subset. */
int summary_te_interp(int c0, int c1, int c2, int c3, int c4, int c5, int c6, int c7)
{
    int expr[9];
    int state[3];
    int i;
    expr[0] = c0;
    expr[1] = c1;
    expr[2] = c2;
    expr[3] = c3;
    expr[4] = c4;
    expr[5] = c5;
    expr[6] = c6;
    expr[7] = c7;
    expr[8] = 0;
    state[0] = 0;
    state[1] = 0;
    state[2] = 0;
    i = 0;
    while (i < 9 && expr[i] != 0) {
        i = i + 1;
    }
    if (i > 0) {
        state[0] = 1;
        state[1] = expr[0];
        state[2] = i;
    }
    if (state[0] != 0) {
        return state[1];
    }
    return 2143289344;
}
