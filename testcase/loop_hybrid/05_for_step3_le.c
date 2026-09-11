int main(int n) { int a[12]; int s = 0; for (int i = 1; i <= 10; i += 3) { a[i] = n + i; s = s + a[i]; } return s; }
