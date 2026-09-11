int main(int n) { int a[5]; int s = 0; for (int i = 0; i < 5; i = i + 1) { a[i] = n + i; } int j = 4; while (j >= 0) { s = s + a[j]; j = j - 1; } return s; }
