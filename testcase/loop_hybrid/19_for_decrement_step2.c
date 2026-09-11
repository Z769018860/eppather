int main(int n) { int a[10]; int s = 0; for (int i = 9; i >= 1; i -= 2) { a[i] = n; s = s + a[i]; } return s; }
