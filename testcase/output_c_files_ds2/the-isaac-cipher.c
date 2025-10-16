void isaac(int randrsl[256], int mm[256], int aa, int bb, int cc, int randcnt)
{
   int i;
   int x;
   int y;

   cc = cc + 1;
   bb = bb + cc;

   for (i=0; i<5; i=i+1)
   {
     x = mm[i];
     if ((i%4) == 0)
     {
        aa = aa^(aa<<13);
     }
     else if ((i%4) == 1)
     {
        aa = aa^(aa>>6);
     }
     else if ((i%4) == 2)
     {
        aa = aa^(aa<<2);
     }
     else if ((i%4) == 3)
     {
        aa = aa^(aa>>16);
     }
     aa = mm[(i+128)%256] + aa;
     mm[i] = y = mm[(x>>2)%256] + aa + bb;
     randrsl[i] = bb = mm[(y>>10)%256] + x;
   }
   randcnt = 0;
   return;
}

void randinit(int flag, int randrsl[256], int mm[256], int aa, int bb, int cc, int randcnt)
{
   int i;
   int a;
   int b;
   int c;
   int d;
   int e;
   int f;
   int g;
   int h;
   aa = 0;
   bb = 0;
   cc = 0;
   a = 2654435769;
   b = 2654435769;
   c = 2654435769;
   d = 2654435769;
   e = 2654435769;
   f = 2654435769;
   g = 2654435769;
   h = 2654435769;

   for (i=0; i<5; i=i+1)
   {
      a = a^(b<<11);
      d = d + a;
      b = b + c;
      b = b^(c>>2);
      e = e + b;
      c = c + d;
      c = c^(d<<8);
      f = f + c;
      d = d + e;
      d = d^(e>>16);
      g = g + d;
      e = e + f;
      e = e^(f<<10);
      h = h + e;
      f = f + g;
      f = f^(g>>4);
      a = a + f;
      g = g + h;
      g = g^(h<<8);
      b = b + g;
      h = h + a;
      h = h^(a>>9);
      c = c + h;
      a = a + b;
   }

   for (i=0; i<5; i=i+1)
   {
      if (flag)
      {
         a = a + randrsl[i];
         b = b + randrsl[i+1];
         c = c + randrsl[i+2];
         d = d + randrsl[i+3];
         e = e + randrsl[i+4];
         f = f + randrsl[i+5];
         g = g + randrsl[i+6];
         h = h + randrsl[i+7];
      }
      a = a^(b<<11);
      d = d + a;
      b = b + c;
      b = b^(c>>2);
      e = e + b;
      c = c + d;
      c = c^(d<<8);
      f = f + c;
      d = d + e;
      d = d^(e>>16);
      g = g + d;
      e = e + f;
      e = e^(f<<10);
      h = h + e;
      f = f + g;
      f = f^(g>>4);
      a = a + f;
      g = g + h;
      g = g^(h<<8);
      b = b + g;
      h = h + a;
      h = h^(a>>9);
      c = c + h;
      a = a + b;
      mm[i] = a;
      mm[i+1] = b;
      mm[i+2] = c;
      mm[i+3] = d;
      mm[i+4] = e;
      mm[i+5] = f;
      mm[i+6] = g;
      mm[i+7] = h;
   }

   if (flag)
   {
      for (i=0; i<5; i=i+1)
      {
         a = a + mm[i];
         b = b + mm[i+1];
         c = c + mm[i+2];
         d = d + mm[i+3];
         e = e + mm[i+4];
         f = f + mm[i+5];
         g = g + mm[i+6];
         h = h + mm[i+7];
         a = a^(b<<11);
         d = d + a;
         b = b + c;
         b = b^(c>>2);
         e = e + b;
         c = c + d;
         c = c^(d<<8);
         f = f + c;
         d = d + e;
         d = d^(e>>16);
         g = g + d;
         e = e + f;
         e = e^(f<<10);
         h = h + e;
         f = f + g;
         f = f^(g>>4);
         a = a + f;
         g = g + h;
         g = g^(h<<8);
         b = b + g;
         h = h + a;
         h = h^(a>>9);
         c = c + h;
         a = a + b;
         mm[i] = a;
         mm[i+1] = b;
         mm[i+2] = c;
         mm[i+3] = d;
         mm[i+4] = e;
         mm[i+5] = f;
         mm[i+6] = g;
         mm[i+7] = h;
      }
   }

   isaac(randrsl, mm, aa, bb, cc, randcnt);
   randcnt = 0;
   return;
}

void iRandom(int randrsl[256], int mm[256], int aa, int bb, int cc, int randcnt)
{
   int r;
   r = randrsl[randcnt];
   randcnt = randcnt + 1;
   if (randcnt > 255)
   {
      isaac(randrsl, mm, aa, bb, cc, randcnt);
      randcnt = 0;
   }
   return;
}

void iRandA(int randrsl[256], int mm[256], int aa, int bb, int cc, int randcnt)
{
   iRandom(randrsl, mm, aa, bb, cc, randcnt);
   return;
}

void iSeed(int flag, int randrsl[256], int mm[256], int aa, int bb, int cc, int randcnt, int seed[256], int m)
{
   int i;
   for (i=0; i<5; i=i+1)
   {
      mm[i] = 0;
   }
   for (i=0; i<5; i=i+1)
   {
      if (i>m)
      {
         randrsl[i] = 0;
      }
      else
      {
         randrsl[i] = seed[i];
      }
   }
   randinit(flag, randrsl, mm, aa, bb, cc, randcnt);
   return;
}

void Vernam(int msg[5], int randrsl[256], int mm[256], int aa, int bb, int cc, int randcnt, int v[5])
{
   int i;
   int l;
   l = 5;
   for (i=0; i<5; i=i+1)
   {
      v[i] = iRandA(randrsl, mm, aa, bb, cc, randcnt) ^ msg[i];
   }
   return;
}

void Caesar(int m, int ch, int shift, int modulo, int start)
{
   int n;
   if (m == 1)
   {
      shift = -shift;
   }
   n = (ch-start) + shift;
   n = n % modulo;
   if (n<0)
   {
      n = n + modulo;
   }
   return;
}

void CaesarStr(int m, int msg[5], int modulo, int start, int randrsl[256], int mm[256], int aa, int bb, int cc, int randcnt, int c[5])
{
   int i;
   int l;
   l = 5;
   for (i=0; i<5; i=i+1)
   {
      Caesar(m, msg[i], iRandA(randrsl, mm, aa, bb, cc, randcnt), modulo, start);
   }
   return;
}
