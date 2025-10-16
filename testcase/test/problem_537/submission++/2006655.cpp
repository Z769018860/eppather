#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=5e6+5;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

int DNA[MAXN],num[MAXN];
int k,maxn=-1;
char c[MAXN];

signed main(){



	std::cin>>c+1;
	int n=strlen(c+1);
	for(int i=1;i<=n;i++) {
		if(c[i]=='A')DNA[i]=0;
		if(c[i]=='G')DNA[i]=1;
		if(c[i]=='C')DNA[i]=2;
		if(c[i]=='T')DNA[i]=3;
	}
	k=read();
	
	for(int i=1;i<=n-k+1;i++){
	    int ans=0;
	    for(int j=0;j<k;j++){
			ans+=DNA[i+j];
			ans<<=2;
		}
		num[ans]++;
		maxn=std::max(maxn,num[ans]);
	}
	println(maxn);

	return 0;
}

