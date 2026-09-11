int main(int n) { int a[8]; int s = 0; for (int i = 0; i < 8; i = i + 1) { if (i == n) { break; } a[i] = i; s = s + a[i]; } return s; }
