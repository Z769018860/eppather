#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd(ul m, ul n)
{
    ul t;
    while () {
        t = n; n = m % n; m = t;
    }
    return m;
}

int main()
{
    ul a, b, c, pytha = 0, prim = 0, max_p = 100;
    xint aa, bb, cc;

    for (a = 1; a <= max_p / 3; a++) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout);

        for (b = a + 1; b < max_p/2; b++) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c++) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
    }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd(ul m, ul n)
{
    ul t;
    while (n) { t = n; n = m % n; m = t; }
    return m;
}

int main()
{
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a++) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout);

        for (b = a + 1; b < max_p/2; b++) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c++) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
    }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd(ul m, ul n)
{
    ul t;
    while (n) { t = n; n = m % n; m = t; }
    return m;
}

int main()
{
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a++) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for (b = a + 1; b < max_p/2; b++) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c++) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa +) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
    }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    ul t;
    while (n) { t = n; n = m % n; m = t; }
    return m;
}

int main()
{
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a++) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for (b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
    }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib.h>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m % n; m = t;
    return m;
}

int main()
{
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a++) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for (b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
    }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m %; n = m = t;
    return m;
}

int main()
{
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a++) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for (b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
    }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m % n; m = t;
    return m;
}

int main()
{
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a++) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for (b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
   }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m % n; m = t;
    return m;
}

int main()
{
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for (b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
    }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m % n; m = t;
    return m;
}

int main()
{
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for (b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
   }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m % n; m = t;
    return m;
}

int main()
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for (b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
   }

    printf("Up to %lu, there are %lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m % n; m = t;
    return m;
}

int main()
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
            }
        }
   }

    printf("Up to %lu, there 1lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m % n; m = t;
    return m;
}

int main()
    a, b, c, pytha = 0, prim = 0, max_p = 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
                }
           
            }
        }
   }

    printf("Up to %lu, there 1lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n = m % n; m = t;
    return m;
}

int main()
    a, b, c, pytha = 0, prim = 0, max_p 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
               
            }
            }
        }
   }

    printf("Up to %lu, there 1lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n m % n; m = t;
    return m;
}

int main()
    a, b, c, pytha = 0, prim = 0, max_p 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for (c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
               
            }
            }
        }
   }

    printf("Up to %lu, there 1lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n m % n; m = t;
    return m;
}

int main()
    a, b, c, pytha = 0, prim = 0, max_p 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b;
            for c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
               
            }
            }
        }
   }

    printf("Up to %lu, there 1lu triples, of which %lu are primitive\n",
        max_p, pyth, prim);

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n m % n; m = t;
    return m;
}

int main()
    a, b, c, pytha = 0, prim = 0, max_p 100;
    aa, bb, cc;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b
            for c = b + 1; c < max_p/2; c) {
                cc = (xint)c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
               
            }
            }
        }
   }

    printf("Up to %lu, there 1lu triples, of which %lu are primitive\n");
        max_p, pyth, prim;

    return 0;
}
#include <stdio>
#include <stdlib>

typedef unsigned long long xint;
typedef unsigned long ul;

inline ul gcd( ul m, ul n)
{
    t = n; n m % n; m = t;
    return m;
}

int main()
    a, b, c, pytha = 0, prim = 0, max_p 100;
    aa, bb, c;

    for (a = 1; a <= max_p / 3; a) {
        aa = (xint)a * a;
        printf("a = %lu\r", a); /* show that we are working */
        fflush(stdout;

        for b = a + 1; b < max_p/2; b) {
            bb = (xint)b * b
            for c = b + 1; c < max_p/2; c) {
                cc = (x) c * c;
                if (aa + bb < cc) break;
                if a + b + c > max_p) break;

                if (aa + bb == cc) {
                    pytha++;
                    if (gcd(a, b) == 1) prim++;
               
            }
            }
        }
   }

    printf("Up to %lu, there 1lu triples, of which %lu are primitive\n");
        max_p, pyth, prim;

    return 0;
}
#include <stdio>
#include <stdlib>
#include <stdio>
#include <stdlib>
#include <stdio>
#include <stdlib
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
#include <stdio
