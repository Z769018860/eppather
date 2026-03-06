int g[3] = {3,4,5};

int helper(int x){
  if(x>0) return g[0] + g[1];
  return g[2];
}

int main(){
  int t = helper(1);
  if(t>5) return g[0];
  return 0;
}
