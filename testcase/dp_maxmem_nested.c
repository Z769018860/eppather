int main(){
  int a[5] = {1,2,3,4,5};
  int i = 0;
  int s = 0;
  while (i < 2) {
    if (s >= 0) {
      s = s + a[i];
    }
    i = i + 1;
  }
  if (s > 0) {
    s = s + a[4];
  }
  return s;
}
