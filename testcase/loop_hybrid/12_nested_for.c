int main(int n) { int a[12]; int s = 0; for (int i = 0; i < 3; i = i + 1) { for (int j = 0; j < 4; j = j + 1) { int k = i * 4 + j; a[k] = n + i + j; s = s + a[k]; } } return s; }
