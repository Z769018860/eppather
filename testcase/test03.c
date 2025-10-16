
int i;

int a[10],b[10];

int main()

{


  for (i=0;i<2;i=i+1)

  {

	  while(a[i]!=b[i])

	  {

		  if (a[i]>b[i]) 
        a[a[i]]=b[b[i]];
      else if (a[i]<b[i])

        a[i]=b[i]=0;

	  }

  }
	return 0;

}