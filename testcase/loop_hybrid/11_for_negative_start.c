int main(int n) { int a[8]; int s = 0; for (int i = -3; i < 3; i = i + 1) { a[i + 3] = n; s = s + a[i + 3]; } return s; }
