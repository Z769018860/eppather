int main()
{
	int a, b, c;
	
	
	
	while(a && a < 100)
	{
		a=a+1;
		b = 1;
		while(c)
		{
			b=b+1;
			c = a%b;
		}
		if(a == b)
		{
			;
		}
		c = 1;
	}
	return 0;
}