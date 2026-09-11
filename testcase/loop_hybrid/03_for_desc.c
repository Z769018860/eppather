int main(int n) { int a[8]; int s = 0; for (int i = 5; i > 0; i = i - 1) { a[i] = n + i; s = s + a[i]; } return s; }
