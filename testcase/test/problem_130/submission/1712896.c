#include <stdio.h>
#include <stdlib.h>
int n;
int main()
{
    void add(long long *fp, long long i, long long x);
    long long sumup(long long *fp, long long x);
    long long q, i, b, c, mm, *fp;
    long long a;
    scanf("%lld %lld", &n, &q);
    fp = (long long*)malloc((n+1) * sizeof(long long));
    for(i = 0; i < n; i++)
    {
        fp[i] = 0;
    }
    for (i = 1; i <= n; i++)
    {
        scanf("%lld", &mm);
        add(fp, i, mm);
    }
    for(i = 0; i < q; i++)
    {
    scanf("%lld %lld %lld", &a, &b, &c);
    if (a == 1)
        add(fp, b, c);
    else
    {
      if (b == 1)
            printf("%lld\n", sumup(fp, c));
      else
        printf("%lld\n", sumup(fp, c) - sumup(fp, b-1));
    }

    }
    return 0;
}
void add(long long *fp, long long i, long long x)
{

  while(i <= n)
  {
      fp[i] += x;
      i += i&(-i);
  }
}
long long sumup(long long *fp, long long x)
{

    long long sum = 0;
    while(x > 0)
    {
       sum += fp[x];
       x -= x&(-x);
    }
    return sum;
}

