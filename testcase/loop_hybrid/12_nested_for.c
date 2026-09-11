int main(int n) { int a[3][4]; int s = 0; for (int i = 0; i < 3; i = i + 1) { for (int j = 0; j < 4; j = j + 1) { a[i][j] = n + i + j; s = s + a[i][j]; } } return s; }
