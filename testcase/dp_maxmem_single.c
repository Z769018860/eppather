int main(){
  int a[4]={1,2,3,4};
  int i=0;
  int s=0;
  while(i<3){
    s = s + a[i];
    i = i + 1;
  }
  if(s>3){
    s = s + a[3];
  }
  return s;
}
