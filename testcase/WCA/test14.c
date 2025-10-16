int a,b,c,d,e;
int main()
{
	
	while(a != b)
	{
		b=b+1;
		c = a%b;
		if(c == 0)
		{
			d=d+1;
			e=e+b;
		}
	}
	
	return 0;
}