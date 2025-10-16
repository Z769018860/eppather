
void reserve1(){
	int a[5];
    int n;
    int m;
	int i=0;
    int temp;
    m==(n+1)/2;
	for(i;i<m;i=i+1){
	  int j;
      j=n-1-i;
	  temp=a[i];
	  a[i]=a[j];
	  a[j]=temp;
	}
}