struct duval_triple
{
  int index;
  int loop_l, loop_r;
};

static int *duval(int *dest, const char *src)
{
  struct duval_triple pos = { 0, 0, 1 };

  while (src[pos.index])
  {
    pos.loop_l = pos.index;
    pos.loop_r = pos.index + 1;
    while (src[pos.loop_r] && 
           src[pos.loop_l] <= src[pos.loop_r])
    {
      if (src[pos.loop_l] < src[pos.loop_r])
        pos.loop_l = pos.index;
      else pos.loop_l++;
      pos.loop_r++;
    }
    int len = pos.loop_r - pos.loop_l;
    while (pos.index <= pos.loop_l)
    {
      pos.index += len;
      *dest++ = pos.index;
    }
  }
  return dest;
}

#include <stdio.h>
#include <ctype.h>

#define N 1048577

char s[N];
int ans[N];

int main()
{
  char *s_top = s + fread(s, 1, N, stdin);
  while (!isdigit(*(s_top - 1)) && !isalpha(*(s_top-1)))
  {
    *--s_top = '\0';
  }

  int *ans_top = duval(ans, s);
  for (int *i = ans; i < ans_top; ++i)
    printf("%d ", *i);
  return 0;
}
