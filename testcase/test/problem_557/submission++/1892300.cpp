#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define FIOBUFSIZ (1<<20|1)
#define NOTONLYDIGIT
struct freader
{
	FILE*f;
#	ifdef ONLINE_JUDGE
		char buf[FIOBUFSIZ],*p1,*p2;
#		define fgetc(f) (p1==p2&&(p2=(p1=buf)+fread(buf,1,FIOBUFSIZ,f),p1==p2)?EOF:*p1++)
#	endif
#	ifdef BOOLTRANS
		bool neof;
#		define NEOF(c) ((c)!=EOF||(neof=0))
#	else
#		define NEOF(c) ((c)!=EOF)
#	endif
#	ifdef NOTONLYDIGIT
#		define isdigit(c) ((c)>='0'&&(c)<='9')
#		define isnotdigit(c) ((c)<'0'||(c)>'9')
#	else
#		define isdigit(c) ((c)>='0')
#		define isnotdigit(c) ((c)<'0')
#	endif
	freader(FILE*_f=stdin):f(_f)
	{
#		ifdef BOOLTRANS
			neof=1;
#		endif
#		ifdef ONLINE_JUDGE
			setvbuf(f,NULL,_IONBF,0);
			p1=p2=buf;
#		endif
	}
#	ifdef NOTONLYDIGIT
		void read(char&x)
		{
			for(x=fgetc(f);NEOF(x)&&x<=' ';x=fgetc(f));
			return;
		}
		void read(char*s)
		{
			for(*s=fgetc(f);NEOF(*s)&&*s<=' ';*s=fgetc(f));
			for(s++;NEOF(*s=fgetc(f))&&*s>' ';s++);
			*s='\0';
			return;
		}
#	endif
	template<typename T>void read(T&x)
	{
		char c(fgetc(f));
#		ifdef NEGATIVE
			for(;NEOF(c)&&isnotdigit(c)&&c!='-';c=fgetc(f));
			if(c=='-')
				for(c=fgetc(f),x=0;NEOF(c)&&isdigit(c);c=fgetc(f))
					x=(x<<3)+(x<<1)-(c^'0');
			else
				for(x=0;NEOF(c)&&isdigit(c);c=fgetc(f))
					x=(x<<3)+(x<<1)+(c^'0');
#		else
			for(;NEOF(c)&&isnotdigit(c);c=fgetc(f));
			for(x=0;NEOF(c)&&isdigit(c);c=fgetc(f))
				x=(x<<3)+(x<<1)+(c^'0');
#		endif
		return;
	}
#	if __cplusplus>=201103
		template<typename T,typename...Args>void read(T&x,Args&...args){return read(x),read(args...);}
#	endif
	template<typename T>freader&operator>>(T&x)
	{
#		ifdef BOOLTRANS
			return *this?read(x),*this:*this;
#		else
			return read(x),*this;
#		endif
	}
#	ifdef BOOLTRANS
		operator bool(){return neof;}
#	endif
#	ifdef ONLINE_JUDGE
#		undef fgetc
#	endif
#	undef NEOF
#	undef isdigit
#	undef isnotdigit
}fin;
struct fwriter
{
	FILE*f;
#	ifdef ONLINE_JUDGE
		char buf[FIOBUFSIZ],*p1;
#		define fputc(c,f) (p1==buf+FIOBUFSIZ?fwrite(buf,1,FIOBUFSIZ,f),*(p1=buf)++=(c):*p1++=(c))
#	endif
	fwriter(FILE*_f=stdout):f(_f)
	{
#		ifdef ONLINE_JUDGE
			setvbuf(f,NULL,_IONBF,0);
			p1=buf;
#		endif
	}
	~fwriter(){flush();}
	void flush()
	{
#		ifdef ONLINE_JUDGE
			fwrite(buf,1,p1-buf,f),p1=buf;
#		else
			fflush(f);
#		endif
		return;
	}
	void write(char c)
	{
		fputc(c,f);
		return;
	}
	void write(char*s)
	{
		for(;*s;s++)
			fputc(*s,f);
		return;
	}
	void write(const char*s)
	{
		for(;*s;s++)
			fputc(*s,f);
		return;
	}
	template<typename T>void write(T x)
	{
		if(!x)
		{
			fputc('0',f);
			return;
		}
		if(x<0)
			fputc('-',f),x=-x;
		char s[41];
		int l(0);
		while(x)
			s[l++]=x%10^'0',x/=10;
		while(l--)
			fputc(s[l],f);
		return;
	}
#	if __cplusplus>=201103
		template<typename T,typename...Args>void write(T x,Args...args){return write(x),write(args...);}
#	endif
	template<typename T>fwriter&operator<<(T x){return write(x),*this;}
#	ifdef ONLINE_JUDGE
#		undef fputc
#	endif
}fout;
#undef FIOBUFSIZ
const int N=1e5+5,S=300,M=405;
unordered_map<int,int> mp;
int n,m,a[N],id[N],tot;
int cnt[M][N*2],la;
int L[M],R[M],lz[M]; 
int d(int x) {return mp[x]?mp[x]:(mp[x]=++tot);}
void cg(int l,int r,int x) {
	int k=id[l];
	if(lz[k]==-1) {
		for(int i=l;i<=r;i++) {
			cnt[k][a[i]]--;
			cnt[k][x]++;a[i]=x;
		}
	} else {
		for(int i=L[k];i<l;i++) a[i]=lz[k];
		for(int i=l;i<=r;i++) a[i]=x;
		for(int i=r+1;i<=R[k];i++) a[i]=lz[k];
		cnt[k][x]+=r-l+1;cnt[k][lz[k]]-=r-l+1;lz[k]=-1;
	}
}
void cg1(int k,int x) {
	if(lz[k]!=-1) cnt[k][lz[k]]=0; 
	else for(int i=L[k];i<=R[k];i++) cnt[k][a[i]]--;
	cnt[k][x]=R[k]-L[k]+1;
	lz[k]=x;
}
int sz(int l,int r,int x) {
	int k=id[l],cnt=0;
	if(lz[k]!=-1) {
		if(x==lz[k]) return r-l+1;
		return 0;
	}
	for(int i=l;i<=r;i++)
		if(a[i]==x) cnt++;
	return cnt;
}
int query(int l,int r,int x,int y) {
	int k=id[l],cnt=0;
	if(lz[k]!=-1) {
		if(x==lz[k]&&(r-l+1)>=y) return l+y-1;
		return 0;
	}
	for(int i=l;i<=r;i++)
		if(a[i]==x) {
			cnt++;
			if(cnt==y) return i;
		}
	return 0;
}
int main() {
	fin>>n>>m; 
	for(int i=1;i<=n;i++) fin>>a[i];
	for(int i=1;i<=n;i++) {
		id[i]=(i-1)/S+1;
		a[i]=d(a[i]);
		cnt[id[i]][a[i]]++;
	}
	for(int l=1,r=S,i=1;l<=n;l+=S,r+=S,i++) L[i]=l,R[i]=min(r,n),lz[i]=-1;
	while(m--) {
		char s[10];
		int l,r,x,y;
		fin>>s>>l>>r>>x;l^=la,r^=la,x^=la;
		if(s[0]=='M') {
			x=d(x);
			if(id[l]==id[r]) cg(l,r,x);
			else {
				int u=id[l]+1,v=id[r]-1;
				cg(l,R[id[l]],x);
				for(int i=u;i<=v;i++) cg1(i,x);
				cg(L[id[r]],r,x);
			}
		} 
		else {
			fin>>y;y^=la;y=d(y);
			if(id[l]==id[r]) printf("%d\n",la=query(l,r,y,x));
			else {
				int u=id[l]+1,v=id[r]-1,e;
				if(x<=(e=sz(l,R[id[l]],y))) {
					printf("%d\n",la=query(l,R[id[l]],y,x));
					continue;
				}
				x-=e;
				for(int i=u;i<=v;i++) {
					if(x<=cnt[i][y]) {
						printf("%d\n",la=query(L[i],R[i],y,x));
						x-=cnt[i][y];
						break;
					}
					x-=cnt[i][y];
				}
				if(x>0) printf("%d\n",la=query(L[id[r]],r,y,x));
			}
		}
	}
}