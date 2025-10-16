#include<bits/stdc++.h>
using namespace std;
int lk[10000005],is,w[9000005],nn[9000005];const int mod=998244353,ll=20,kl=1<<ll;
int ww(int x,int y){
	if(!x)return 0;if(y==mod-2&&x<=kl&&nn[x])return nn[x];
	int kk=1;while(y){if(y&1)kk=1ll*kk*x%mod;x=1ll*x*x%mod,y>>=1;}return kk;
}
template<typename T>inline void read(T &n){
	T w=1;n=0;char ch=getchar();
	while(!isdigit(ch)&&ch!=EOF){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)&&ch!=EOF)n=(n<<1)+(n<<3)+(ch&15),ch=getchar();
	n*=w;
}
struct poly{
	int*a,si;
	poly(const int&aa=0):a(lk+is),si(aa){is+=aa;}
	void in(){for(int g=0;g<si;g++)read(a[g]);}
	void out()const{for(int g=0;g<si;g++)cout<<a[g]<<' ';}
	void out(const int&aa)const{
		for(int g=0;g<si&&g<aa;g++)cout<<a[g]<<' ';for(int g=si;g<aa;g++)cout<<"0 ";
	}
	void put(poly&aa)const{
		for(int g=0;g<si&&g<aa.si;g++)aa.a[g]=a[g];for(int g=si;g<aa.si;g++)aa.a[g]=0;
	}
	poly sub(const int&aa)const{poly kk(aa);put(kk);return kk;}
	poly sub()const{poly kk(si);put(kk);return kk;}
	poly cut(const int&aa=0){si=min(si,aa);return*this;}
	poly operator+(const poly&aa)const{
		poly kk(max(si,aa.si));put(kk);for(int g=0;g<aa.si;g++)kk.a[g]=(kk.a[g]+aa.a[g])%mod;
		return kk;
	}
	poly operator-(const poly&aa)const{
		poly kk(max(si,aa.si));put(kk);
		for(int g=0;g<aa.si;g++)kk.a[g]=(kk.a[g]+mod-aa.a[g])%mod;return kk;
	}
	poly operator+(const int&aa)const{poly kk=sub();kk.a[0]=(kk.a[0]+aa)%mod;return kk;}
	poly operator-(const int&aa)const{poly kk=sub();kk.a[0]=(kk.a[0]+mod-aa)%mod;return kk;}
	void IDFT(int*&a,const int&k2=0)const{
		int*aa[2];aa[k2&1]=a,aa[k2&1^1]=lk+is;
		for(int g=k2-1;g>=0;g--)
			for(int h=0;h<(1<<k2);h+=1<<g)
				for(int j=0;j<(1<<g);j++){
					int k=(h<<1)&((1<<k2)-1);
					aa[g&1][h|j]=(aa[g&1^1][k|j]+1ll*aa[g&1^1][k|j|1<<g]*w[h<<(ll-k2)])%mod;
				}
		if(k2&1)for(int g=0;g<(1<<k2);g++)a[g]=aa[0][g];
	}
	void DFT(int*&a,const int&k2=0)const{
		int*aa[2];aa[k2&1]=a,aa[k2&1^1]=lk+is;
		for(int g=k2-1;g>=0;g--)
			for(int h=0;h<(1<<k2);h+=1<<g)
				for(int j=0;j<(1<<g);j++){
					int k=(h<<1)&((1<<k2)-1);
					aa[g&1][h|j]=(aa[g&1^1][k|j]+1ll*aa[g&1^1][k|j|1<<g]*w[kl-(h<<(ll-k2))])
					%mod;
				}
		if(k2&1)for(int g=0;g<(1<<k2);g++)a[g]=aa[0][g];
	}
	poly operator*(const poly&aa)const{
		poly kk(si+aa.si-1);const int k1=is;int k2=kk.si-1,k3=0;while(k2)k2>>=1,k3++;int*l1,*l2;
		l1=lk+is,is+=1<<k3,l2=lk+is,is+=1<<k3;for(int g=0;g<(1<<k3);g++)l1[g]=l2[g]=0;
		for(int g=0;g<si;g++)l1[g]=a[g];for(int g=0;g<aa.si;g++)l2[g]=aa.a[g];IDFT(l1,k3),
		IDFT(l2,k3);for(int g=0;g<(1<<k3);g++)l1[g]=1ll*l1[g]*l2[g]%mod;DFT(l1,k3),
		k2=ww(1<<k3,mod-2);for(int g=0;g<kk.si;g++)kk.a[g]=1ll*l1[g]*k2%mod;is=k1;return kk;
	}
	poly ni(const int&aa=0)const{
		poly kk(aa);const int k1=is;int k2=1;poly l1(1);l1.a[0]=ww(a[0],mod-2);
		while(k2<aa)k2<<=1,l1=l1+l1-(l1*l1*sub(k2)).cut(k2);l1.put(kk),is=k1;return kk;
	}
	poly dao()const{
		poly kk(max(si-1,1));kk.a[0]=0;for(int g=1;g<si;g++)kk.a[g-1]=1ll*a[g]*g%mod;return kk;
	}
	poly ji()const{
		poly kk(si+1);kk.a[0]=0;for(int g=0;g<si;g++)kk.a[g+1]=1ll*a[g]*ww(g+1,mod-2)%mod;
		return kk;
	}
	poly ln(const int&aa=0)const{
		if(a[0]!=1){lk[is]=0;return poly(1);}poly kk(aa);const int k1=is;
		(sub(aa).dao()*sub(max(aa-1,1)).ni(max(aa-1,1))).cut(max(aa-1,1)).ji().cut(aa).put(kk);
		is=k1;return kk;
	}
	poly exp(const int&aa=0)const{
		if(a[0]){lk[is]=0;return poly(1);}poly kk(aa);const int k1=is;poly l1(1);l1.a[0]=1;
		int k2=1;while(k2<aa)k2<<=1,l1=((sub(k2)+1-l1.ln(k2))*l1).cut(k2);l1.put(kk),is=k1;
		return kk;
	}
};
int a[100005];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	w[0]=1,w[1]=ww(3,(mod-1)/kl);for(int g=2;g<=kl;g++)w[g]=1ll*w[g-1]*w[1]%mod;
	for(int g=1;g<=kl;g++)nn[g]=ww(g,mod-2);
	int s,d,o,i;read(s),read(d);int kk=1;
	for(int g=1;g<=d;g++){
		read(o),read(i);if(!o){kk=1ll*kk*(i+1)%mod;continue;}
		if(o<=s)a[o]=(a[o]+mod-1)%mod;
		if(i&&i+1<=s/o)a[o*(i+1)]=(a[o*(i+1)]+1)%mod;
	}
	poly l1(s+1);
	for(int g=1;g<=s;g++)for(int h=1;h*g<=s;h++)
	l1.a[g*h]=(l1.a[g*h]+mod-1ll*a[g]*ww(h,mod-2)%mod)%mod;
	l1=l1.exp(s+1);for(int g=1;g<=s;g++)cout<<l1.a[g]<<'\n';
	return 0;
}