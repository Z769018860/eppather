#include <stdio.h>
#include <ctype.h>

char *ss;
char buffer[1<<25];

inline int read(){
	register int bufin,chr;
	while (!isdigit(chr=*ss++));bufin=chr-'0';
	while (isdigit(chr=*ss++))bufin=bufin*10+chr-'0';
	return bufin;
}

const int MOD=1e9+9;

inline int add(int a,int b){return (a+=b)>=MOD?(a-MOD):a;}
inline int minus(int a,int b){return (a-=b)<0?(a+MOD):a;}

void FMT(int* a,int len){
	for (int i=1,s=2;i<len;i<<=1,s<<=1)
		for (int j=0;j<len;j+=s)
			for (int k=0;k<i;k++)
				a[i+j+k]=add(a[i+j+k],a[j+k]);
}

void IFMT(int* a,int len){
	for (int i=1,s=2;i<len;i<<=1,s<<=1)
		for (int j=0;j<len;j+=s)
			for (int k=0;k<i;k++)
				a[i+j+k]=minus(a[i+j+k],a[j+k]);
}

int n,L;
int count[1<<20|1];
int F[21][1<<20|1];
int g[21][1<<20|1];
int h[21][1<<20|1];

int main (){
	fread(ss=buffer,1,1<<25,stdin);
	n=read();
	L=1<<n;
	for (int i=0;i<L;i++)count[i]=count[i>>1]+(i&1);
	for (int i=0;i<L;i++)F[count[i]][i]=read();
	for (int i=0;i<L;i++)g[count[i]][i]=read();
	for (int i=0;i<=n;i++)FMT(F[i],L),FMT(g[i],L);
	for (int i=0;i<=n;i++){
		for (int j=0;j<=i;j++)
			for (int k=0;k<L;k++)
				h[i][k]=add(h[i][k],1LL*F[j][k]*g[i-j][k]%MOD);
		IFMT(h[i],L);
	}
	for (int i=0;i<L;i++)
		printf("%d%c",h[count[i]][i]," \n"[i==L-1]);
	return 0;
}
