int isaac(int mm[256], int randrsl[256], int aa, int bb, int cc)
{
   int i;
   int x;
   int y;
   
   cc = cc + 1;
   bb = bb + cc;
   
   for (i = 0; i < 256; i = i + 1)
   {
      x = mm[i];
      if ((i % 4) == 0)
      {
         aa = aa ^ (aa << 13);
      }
      else if ((i % 4) == 1)
      {
         aa = aa ^ (aa >> 6);
      }
      else if ((i % 4) == 2)
      {
         aa = aa ^ (aa << 2);
      }
      else if ((i % 4) == 3)
      {
         aa = aa ^ (aa >> 16);
      }
      aa = mm[(i + 128) % 256] + aa;
      y = mm[(x >> 2) % 256] + aa + bb;
      mm[i] = y;
      randrsl[i] = bb = mm[(y >> 10) % 256] + x;
   }
   return 0;
}

int randinit(int flag, int mm[256], int randrsl[256], int aa, int bb, int cc)
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
   a = 0x9e3779b9;
   b = 0x9e3779b9;
   c = 0x9e3779b9;
   d = 0x9e3779b9;
   e = 0x9e3779b9;
   f = 0x9e3779b9;
   g = 0x9e3779b9;
   h = 0x9e3779b9;
   
   for (i = 0; i < 4; i = i + 1)
   {
      a = a ^ (b << 11);
      d = d + a;
      b = b + c;
      b = b ^ (c >> 2);
      e = e + b;
      c = c + d;
      c = c ^ (d << 8);
      f = f + c;
      d = d + e;
      d = d ^ (e >> 16);
      g = g + d;
      e = e + f;
      e = e ^ (f << 10);
      h = h + e;
      f = f + g;
      f = f ^ (g >> 4);
      a = a + f;
      g = g + h;
      g = g ^ (h << 8);
      b = b + g;
      h = h + a;
      h = h ^ (a >> 9);
      c = c + h;
      a = a + b;
   }
   
   for (i = 0; i < 256; i = i + 8)
   {
      if (flag)
      {
         a = a + randrsl[i];
         b = b + randrsl[i + 1];
         c = c + randrsl[i + 2];
         d = d + randrsl[i + 3];
         e = e + randrsl[i + 4];
         f = f + randrsl[i + 5];
         g = g + randrsl[i + 6];
         h = h + randrsl[i + 7];
      }
      a = a ^ (b << 11);
      d = d + a;
      b = b + c;
      b = b ^ (c >> 2);
      e = e + b;
      c = c + d;
      c = c ^ (d << 8);
      f = f + c;
      d = d + e;
      d = d ^ (e >> 16);
      g = g + d;
      e = e + f;
      e = e ^ (f << 10);
      h = h + e;
      f = f + g;
      f = f ^ (g >> 4);
      a = a + f;
      g = g + h;
      g = g ^ (h << 8);
      b = b + g;
      h = h + a;
      h = h ^ (a >> 9);
      c = c + h;
      a = a + b;
      mm[i] = a;
      mm[i + 1] = b;
      mm[i + 2] = c;
      mm[i + 3] = d;
      mm[i + 4] = e;
      mm[i + 5] = f;
      mm[i + 6] = g;
      mm[i + 7] = h;
   }
   
   if (flag)
   {
      for (i = 0; i < 256; i = i + 8)
      {
         a = a + mm[i];
         b = b + mm[i + 1];
         c = c + mm[i + 2];
         d = d + mm[i + 3];
         e = e + mm[i + 4];
         f = f + mm[i + 5];
         g = g + mm[i + 6];
         h = h + mm[i + 7];
         a = a ^ (b << 11);
         d = d + a;
         b = b + c;
         b = b ^ (c >> 2);
         e = e + b;
         c = c + d;
         c = c ^ (d << 8);
         f = f + c;
         d = d + e;
         d = d ^ (e >> 16);
         g = g + d;
         e = e + f;
         e = e ^ (f << 10);
         h = h + e;
         f = f + g;
         f = f ^ (g >> 4);
         a = a + f;
         g = g + h;
         g = g ^ (h << 8);
         b = b + g;
         h = h + a;
         h = h ^ (a >> 9);
         c = c + h;
         a = a + b;
         mm[i] = a;
         mm[i + 1] = b;
         mm[i + 2] = c;
         mm[i + 3] = d;
         mm[i + 4] = e;
         mm[i + 5] = f;
         mm[i + 6] = g;
         mm[i + 7] = h;
      }
   }
   
   isaac(mm, randrsl, aa, bb, cc);
   return 0;
}

int iRandom(int randrsl[256], int randcnt)
{
   int r;
   r = randrsl[randcnt];
   randcnt = randcnt + 1;
   if (randcnt > 255)
   {
      isaac(mm, randrsl, aa, bb, cc);
      randcnt = 0;
   }
   return r;
}

char iRandA(int randrsl[256], int randcnt)
{
   return (char)(iRandom(randrsl, randcnt) % 95 + 32);
}

int iSeed(char seed[256], int flag, int mm[256], int randrsl[256])
{
   int i;
   int m;
   for (i = 0; i < 256; i = i + 1)
   {
      mm[i] = 0;
   }
   m = 0;
   while (seed[m] != 0)
   {
      m = m + 1;
   }
   for (i = 0; i < 256; i = i + 1)
   {
      if (i > m)
      {
         randrsl[i] = 0;
      }
      else
      {
         randrsl[i] = (int)seed[i];
      }
   }
   randinit(flag, mm, randrsl, aa, bb, cc);
   return 0;
}

char Caesar(int m, char ch, char shift, char modulo, char start)
{
   int n;
   if (m == 1)
   {
      shift = -shift;
   }
   n = (ch - start) + shift;
   n = n % modulo;
   if (n < 0)
   {
      n = n + modulo;
   }
   return (char)(start + n);
}

int Vernam(char msg[4096], char v[4096], int randrsl[256], int randcnt)
{
   int i;
   int l;
   l = 0;
   while (msg[l] != 0)
   {
      l = l + 1;
   }
   for (i = 0; i < l; i = i + 1)
   {
      v[i] = iRandA(randrsl, randcnt) ^ msg[i];
   }
   v[l] = 0;
   return 0;
}

int CaesarStr(int m, char msg[4096], char c[4096], char modulo, char start, int randrsl[256], int randcnt)
{
   int i;
   int l;
   l = 0;
   while (msg[l] != 0)
   {
      l = l + 1;
   }
   for (i = 0; i < l; i = i + 1)
   {
      c[i] = Caesar(m, msg[i], iRandA(randrsl, randcnt), modulo, start);
   }
   c[l] = 0;
   return 0;
}

return;
