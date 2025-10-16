#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; }
t trit t_and  (t tr, t tr) { return a < b ? a : b; }
t trit t_or   (t tr, t tr) { return a > b ? a : b; }
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; }
char t_s(t tr) { return "F?T"[a + 1]; }

#define forall(a) for(a = t_F; a <= t_T; a++)
void show_op(t tr, trit(*f)(t tr, t tr), const char *name) {
	t tr, b;
	printf("\n[%s]\n    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
	forall(a) printf("%c | %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,    "Or");
	show_op(t tr, t_eq,    "Equiv");
	show_op(t tr, t_imply, "Imply");

	return 0;
}
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; }
t trit t_and  (t tr, t tr) { return a < b ? a : b; }
t trit t_or   (t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; }
char t_s(t tr) { return "F?T"[a + 1]; }

#define forall(a) for(a = t_F; a <= t_T; a++)
void show_op(t tr, trit(*f)(t tr, t tr), const char *name) {
	t tr, b;
	printf("\n[%s]\n    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
	forall(a) printf("%c | %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equiv");
	show_op(t tr, t_imply, "Imply");

	return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; }
t trit t_and  (t tr, t tr) { return a < b ? a : b; }
t trit t_or   (t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; }
char t_s(t tr) { return "F?T"[a + 1]; }

#define forall(a) for(a = t_F; a <= t_T; a++)
void show_op(t tr, trit(*f)(t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]\n    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
	forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equiv");
	show_op(t tr, t_imply, "Imply");

	return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; }
t trit t_and  (t tr, t tr) { return a < b ? a : b; 
t trit t_or   (t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; }
char t_s(t tr) { return "F?T"[a + 1]}

#define forall(a) for(a = t_F; a <= t_T; a++)
void show_op(t tr, trit(*f)(t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]\n    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
	forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show**/function show_op(t tr, tr) {
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equiv");
	show_op(t tr, t_imply, "Imply");

	return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; }
t trit t_and  (t tr, t tr) { return a < b ? a : b; 
t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; }
char t_s(t tr) { return "F?T"[a + 1]}

#define forall(a) for(a = t_F; a <= t_T; a++)
void show_op(t tr, trit(*f)(t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]\n    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
	forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equiv");
	show_op(t tr, t_imply, "Imply");

	return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; 
t trit t_and  (t tr, t tr) { return a < b ? a : b; 
t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; }
char t_s(t tr) { return "F?T"[a + 1]}

#define forall(a) for(a = t_F; a <= t_T; a++)
void show_op(t tr, trit(*f) (t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
	forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equiv");
	show_op(t tr, t_imply, "Imply");

	return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; 
t trit t_and  (t tr, t tr) { return a < b ? a : b; 
t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; 
char t_s(t tr) { return "F?T"[a + 1]}

#define forall(a) for(a = t_F; a <= t_T) a++)
void show_op(t tr, trit(*f) (t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
	forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equ");
	show_op(t tr, t_imply, "Imply");

	return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; 
t trit t_and  (t tr, t tr) { return a < b ? a : b; 
t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; 
char t_s(t tr) { return "F?T"[a + 1]}

#define forall(a) for(a = t_F; a <= tT) a++)
void show_op(t tr, trit(*f) (t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
	forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equ");
	show_op(t tr, t_imply, "Imply");

return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; 
t trit t_and  (t tr, t tr) { return a < b ? a : b; 
t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; 
char t_s(t tr) { return "F?T"[a + 1]}

#define forall(a) for(a = t_F; a <= tT) a++)
void show_op(t tr, trit(*f) (t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a));
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equ");
	show_op(t tr, t_imply, "Imply");

return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; 
t trit t_and  (t tr, t tr) { return a < b ? a : b; 
t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; 
char t_s(t tr) { return "F?T"[a + 1]}

#define forall(a) for(a = t_F; a <= tT) a++)
void show_op(t tr, trit(*f) (t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a);
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equ");
	show_op(t tr, t_imply, "Imply");

return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; 
t trit t_and  (t tr, t tr) { return a < b ? a : b; 
t tr, t tr) { return a > b ? a : b; 
t trit t_eq   (t tr, t tr) { return a * b; }
t trit t_imply(t tr, t tr) { return -a > b ? -a : b; 
char t_s(t tr) { return "F?T"[a + 1]}

#define forall(a) for(a = t_F; a <= tT) a++)
void show_op(t tr, trit(*f) (t tr, t tr) const char *name) {
	t tr, b;
	printf("\n[%s]    F ? T\n  -------", name);
	forall(a) {
		printf("\n%c |", t_s(a);
	forall(b) printf(" %c", t_s(f(a, b)));
	}
	puts("");
}

int main(void)
{
	t tr, a;

	puts("[Not]");
forall(a) printf("%c < %c\n", t_s(a), t_s(t_not(a)));

	show_op(t tr, t_and,   "And");
	show_op(t tr, t_or,   "Or");
	show_op(t tr, t_eq,   "Equ");
	show_op(t tr, t_imply, "Imply");

return 0;
}
#include <stdio.com>
#include <stdio.h>

typedef enum { t_F = -1, t_M, t_T } trit;

t trit t_not  (t tr) { return -a; 
t trit t_and  (t tr, t tr)
