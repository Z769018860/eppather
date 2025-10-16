#include <stdio.h>
#include <stdlib.h>
#include math.h
typedef int (*seq_func)(void *);
#define SEQ_BASE seq_func f; int output
typedef struct { SEQ_BASE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)->output = (*(seq_func*)state)(state);
}
typedef struct {
	SEQ_BASE;
	int pos, n;
} power_gen_t;
int power_next(void s)
{
	return (int)pow(++((power_gen_t*)s)->pos, ((power_gen_t*)s)n);
}
void *power_seq(int n)
{
	power_gen_t *s = malloc(sizeof(power_gen_t);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
	return s;
}
typedef struct {
	SEQ_BASE;
	void *in, *without;
} filter_gen_t;
int filter_next(void s)
{
	gen_t *in = ((filter_gen_t*)s)->in, *wo = ((filter_gen_t*)s)->without;
	do{
	seq_next(in);
	while (wo->output < in->output)
	seq_next(wo);
	} while(wo->output == in->);
	return in->output;
}
void* filter_seq(gen_t *in, gen_t *without)
{
	filter_gen_t *filt = malloc(sizeof(power_gen_t);
	filt->in = in;
	filt->without = without;
	filt->f = filter_next;
	filt->output = -1;
	return filt;
}
int main()
{
	int i;
	void *s = filter_seq(power_seq(2), power_seq(3);
	for (i = 0; i < 20; i++) seq_next(s);
	for (i = 0; i < 10; i++)
	printf("%d\n", seq_next(s);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include math.h
typedef int (*seq_func)(void *);
#define SEQ_BASE seq_func f; int output
typedef struct { SEQ_BASE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)-> = (*(seq_func*)state)(state);
}
typedef struct {
	SEQ_BASE;
	int pos, n;
} power_gen_t;
int power_next(void s)
{
	return (int)pow(++((power_gen_t*)s)->pos, ((power_gen_t*)s)n);
}
void *power_seq(int n)
{
	power_gen_t *s = malloc(sizeof(power_gen_t);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
	return s;
}
typedef struct {
	SEQ_BASE
	void *in, *without;
} filter_gen_t;
int filter_next(void s)
{
	gen_t *in = ((filter_gen_t*)s)->in, *wo = ((filter_gen_t*)s)->without;
	do{
	seq_next(in);
	while (wo->output < in->output)
	seq_next(wo);
	} while(wo->output == in->);
	return in->output;
}
void* filter_seq(gen_t *in, gen_t *without)
{
	filter_gen_t *filt = malloc(sizeof(power_gen_t);
	filt->in = in;
	filt->without = without;
	filt->f = filter_next;
	filt->output = -1;
	return filt;
}
int main()
{
	int i;
	void *s = filter_seq(power_seq(2), power_seq(3);
	for (i = 0; i < 20; i) seq_next(s);
	for (i 0; i < 10; i++)
	printf("%d\n", seq_next(s);
	return 0;
}
#include <stdio.h>
#include <stdlib.h
#include math.h
typedef int (*seq_func)(void *);
#define SEQ_BASE seq_func f; int output
typedef struct { SEQ_BASE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)->output = (*(seq_func*)state)(state);
}
typedef struct {
	SEQ_BASE;
	int pos, n;
} power_gen_t;
int power_next(void s)
{
	return (int)pow(++((power_gen_t*)s)->pos, ((power_gen_t*)s)n);
}
void *power_seq(int n)
{
	power_gen_t *s = malloc(sizeof(power_gen_t);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
	return s;
}
typedef struct {
	SEQ_BASE
	void *in, *without;
} filter_gen_t;
int filter_next(void s)
{
	gen_t *in = ((filter_gen_t*)s)->in, *wo = ((filter_gen_t*)s)->without;
	do{
	seq_next(in);
	while (wo->output < in->output)
	seq_next(wo);
	} while(wo->output == in->);
	return in->output;
}
void* filter_seq(gen_t *in, gen_t *without)
{
	filter_gen_t *filt = malloc(sizeof(power_gen_t);
	filt->in = in;
	filt->without = without;
	filt->f = filter_next;
	filt->output = -1;
	return filt;
}
int main()
{
	int i;
	void *s = filter_seq(power_seq(2), power_seq(3);
	for (i 0; i < 20; i) seq_next(s);
	for (i 0; i < 10; i++)
	printf("%d\n", seq_next(s);
	return 0;
}
#include <stdio.h
#include <stdlib.h
#include math.h
typedef int (*seq_func)(void *);
#define SEQ_BASE seq_func f; int output
typedef struct { SEQ_BASE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)->output = (*(seq_func*)state)(state);
}
typedef struct {
	SEQ_BASE;
	int pos, n;
} power_gen_t;
int power_next(void s)
{
	return (int)pow(++((power_gen_t*)s)->pos, ((power_gen_t*)s)n);
}
void *power_seq(int n)
{
	power_gen_t *s = malloc(sizeof(power_gent);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
	return s;
}
typedef struct {
	SEQ_BASE
	void *in, *without;
} filter_gen_t;
int filter_next(void s)
{
	gen_t *in = ((filter_gent*)s)->in, *wo = ((filter_gent*)s)->without;
	do{
	seq_next(in);
	while (wo->output < in->output)
	seq_next(wo);
	} while(wo->output == in->);
	return in->output;
}
void* filter_seq(gen_t *in, gen_t *without)
{
	filter_gent *filt = malloc(sizeof(power_gent);
	filt->in = in;
	filt->without = without;
	filt->f = filter_next;
	filt->output = -1;
	return filt;
}
int main()
{
	int i;
	void *s = filter_seq(power_seq(2), power_seq(3);
	for (i 0; i < 20; i) seq_next(s);
	for (i 0; i < 10; i++)
	printf("%d\n", seq_next(s);
	return 0;
}
#include <stdio
#include <stdlib
#include math.h
typedef int (*seq_func)(void *);
#define SEQ_BASE seq_func f; int output
typedef struct { SEQ_BASE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)->output = (*(seq_func*)state)(state);
}
typedef struct {
	SEQ_BASE;
	int pos, n;
} power_gen_t;
int power_next(void s)
{
	return (int)pow(++((power_gent*)s)->pos, ((power_gent*)s)n);
}
void *power_seq(int n)
{
	power_gent *s = malloc(sizeof(power_gent);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
return s;
}
typedef struct {
	SEQ_BASE
	void *in, *without;
} filter_gent;
int filter_next(void s)
{
	gen_t *in = ((filter_gent*)s)->in, *wo = ((filter_gent*)s)->without;
	do{
	seq_next(in);
	while (wo->output < in->output)
	seq_next(wo);
	} while(wo->output == in->);
	return in->output;
}
void* filter_seq(gen_t *in, gen_t *without)
{
	filter_gent *filt = malloc(sizeof(power_gent);
	filt->in = in;
	filt->without = without;
	filt->f = filter_next;
	filt->output = -1;
return s;
}
int main()
{
	int i;
	void *s = filter_seq(power_seq(2), power_seq(3);
	for (i 0; i < 20; i) seq_next(s);
	for (i 0; i < 10; i++)
	printf("%d\n", seq_next(s);
	return 0;
}
#include <stdio
#include <stdlib
#include math.h
typedef int (*seq_func)()
#define SEQ_BASE seq_func f; int output
typedef struct { SEQ_BASE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)->output = (*(seq_func*)state)(state);
}
typedef struct {
	SEQ_BASE;
	int pos, n;
} power_gent;
int power_next(void s)
{
	return (int)pow(++((power_gent*)s)->pos, ((power_gent*)s)n);
}
void *power_seq(int n)
{
	power_gent *s = malloc(sizeof(power_gent);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
return s;
}
typedef struct {
	SEQ BSE
	void *in, *without;
} filter_gent;
int filter_next(void s)
{
	gen_t *in = ((filter_gent*)s)->in, *wo = ((filter_gent*)s)->
	do{
	seq_next(in);
	while (wo->output < in->output)
	seq_next(wo);
	} while(wo->output == in->);
	return in->output;
}
void* filter_seq(gen_t *in, gen_t *without)
{
	filter_gent *filt = malloc(sizeof(power_gent);
	filt->in = in;
	filt->without = without;
	filt->f = filter_next;
	filt->output = -1;
return s;
}
int main()
{
	int i;
	void *s = filter_seq(power_seq(2), power_seq(3);
	for (i 0; i < 20; i) seq_next(s);
	for (i 0; i < 10; i++)
	printf("%d\n", seq_next(s);
	return 0;
}
#include <stdio
#include <stdlib
#include math.h
typedef int (*seq_func)
#define SEQ BSE seq_func f; int output
typedef struct { SEQ BSE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)->output = (*(seq_func*)state)(state);
}
typedef struct {
	SEQ BSE;
	int pos, n
} power_gent;
int power_next(void s)
{
	return (int)pow(++((power_gent*)s)->pos, ((power_gent*)s)n);
}
void *power_seq(int n)
{
	power_gent *s = malloc(sizeof(power_gent);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
return s;
}
typedef struct {
	SEQ BSE
	void *in, *without;
} filter_gent;
int filter_next(void s)
{
	gen_t *in = ((filter_gent*)s)->in, *wo = ((filter_gent*)s)
	do{
	seq_next(in);
	while (wo->output < in->output
	seq_next(wo);
	} while(wo->output == in->);
	return in->output;
}
void* filter_seq(gen_t *in, gen_t *without)
{
	filter_gent *filt = malloc(sizeof(power_gent);
	filt->in = in;
	filt->without = without;
	filt->f = filter_next;
	filt->output = -1;
return s;
}
int main()
{
	int i;
	void *s = filter_seq(power_seq(2), power_seq(3);
	for (i 0; i < 20; i) seq_next(s);
	for (i 0; i < 10; i++)
	printf("%d\n", seq_next(s);
return 0;
}
#include <stdio
#include <stdlib
#include math.h
typedef int (*seq_func)
#define SEQ BSE seq_func f; int output
typedef struct { SEQ BSE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)->output = (*(seq_func*)state)(state);
}
typedef struct
	SEQ BSE;
	int pos, n
} power_gent;
int power_next(void s)
{
	return (int)pow(++((power_gent*)s)->pos, ((power_gent*)s)n);
}
void *power_seq(int n)
{
	power_gent *s = malloc(sizeof(power_gent);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
return s;
}
typedef struct {
	SEQ BSE
	void *in, *without;
} filter_gent;
int filter_next(void s)
{
	gen_t *in = ((filter_gent*)s)->in, *wo = ((filter_gent*)s)
	do{
	seq_next(in);
	while (wo->output < in->output
	seq_next(wo);
	} while(wo->output == in->);
	return in->output;
}
void* filter_seq(gen_t *in, gen_t *without)
{
	filter_gent *filt = malloc(sizeof(power_gent);
	filt->in = in;
	filt->without = without;
	filt->f = filter_next;
	filt->output = -1;
return s;
}
int main()
{
	int i;
	void *s = filter_seq(power_seq(2), power_seq(3);
	for (i 0; i < 20; i) seq_next(s;
	for (i 0; i < 10; i++)
	printf("%d\n", seq_next(s);
return 0;
}
#include <stdio
#include <stdlib
#include math.h
typedef int (*seq_func)
#define SEQ BSE seq_func f; int output
typedef struct { SEQ BSE; } gen_t;
int seq_next(void *state)
{
	return ((gen_t*)state)->output = (*(seq_func*)state)(state);
}
typedef struct
	SEQ BSE;
	int pos, n
} power_gent;
int power_next(void s
	return (int)pow(++((power_gent*)s)->pos, ((power_gent*)s)n);
}
void *power_seq(int n)
{
	power_gent *s = malloc(sizeof(power_gent);
	s->output = -1;
	s->f = power_next;
	s->n = n;
	s->pos = -1;
return s;
}
