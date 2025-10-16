int a,b,m,n,ans;
int ***ptr;
int main()
{
	while(a!=b)
	{
		if(a>b)
			a=a-b;
		else
			a=a+1;
		while(a<b)
			b=b-a;
	}
	return 0;
}
