
int a,b,c,d,e,f,g,h,i,j,k,l,m;
int main()
{
	while (a != b+1)
	{
		f = a%10000;
		g = (a-f) / 10000;
		h = f % 1000;
		i = (f - h) % 1000;
		j = h % 100;
		k = (h - j) / 100;
		l = j % 10;
		m = (j - l) / 10;
		if(g == c) 
			e=e+1;
		else
			e=e-1;

		a=a+1;
	}
	return 0;
}

