int main(int n) { int a[6]; int *p = a; int s = 0; for (int i = 0; i < 6; i = i + 1) { *p = n + i; s = s + *p; p = p + 1; } return s; }
