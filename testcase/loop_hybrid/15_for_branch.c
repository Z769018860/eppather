int main(int n) { int a[8]; int s = 0; for (int i = 0; i < 6; i = i + 1) { if (i < n) { a[i] = n; } else { a[i] = i; } s = s + a[i]; } return s; }
