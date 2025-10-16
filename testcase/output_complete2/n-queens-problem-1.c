void solve(int n, int col, int hist[5], int count[1])
{
    if (col == n) {
        count[0] = count[0] + 1;
        return;
    }

    for (int i = 0; i < n; i = i + 1) {
        int j = 0;
        for (j = 0; j < col; j = j + 1) {
            int temp1 = hist[j] == i;
            int temp2 = hist[j] - i;
            if (temp2 < 0) {
                temp2 = -temp2;
            }
            int temp3 = temp2 == col - j;
            if (temp1 || temp3) {
                break;
            }
        }
        if (j < col) {
            continue;
        }

        hist[col] = i;
        solve(n, col + 1, hist, count);
    }
    return;
}
