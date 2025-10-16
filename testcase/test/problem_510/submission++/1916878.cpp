#include<bits/stdc++.h>
#define ll int
#define N 200005
using namespace std;
inline char nc(){
	static char buf[1000000],*p=buf,*q=buf;
	return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++;
}
inline ll read(){
	ll res = 0;
	char c = nc();
	while(c<'0'||c>'9')c=nc();
	while(c<='9'&&c>='0')res=res*10+c-'0',c=nc();
	return res;
}
char obuf[1<<21],*p3=obuf; 
inline void pc(char c){ 
	p3-obuf<=(1<<20)?(*p3++=c):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=c); 
} 
inline void write(ll x){ 
	if(x<0) pc('-'),x=-x; 
	if(x>9) write(x/10); 
	pc(x%10+'0'); 
}
struct node{ll l,r,s;}tr[N<<7];
vector<ll> cir[N];
ll n,q,k,i,j,op,vis[N],tot,in_head[N],in_circle[N],jw[N],las,cnt,head_cir[N],id,now,root[N],tr_tot,jw_cir[N],ans,temp,dep,id_dep[N],num[N],numz,len[N];
ll ttt,ttt2,ttt3,numm,depp;
long long qmi[N],x,y,head;
unordered_map<ll,ll> calc;
unordered_map<long long,ll> get_id[35];
unordered_map<long long,ll> get_id2[N];
inline ll lowbit(ll x){while(x){if(x%k) return x%k;x/=k;}return 0;}
inline ll lowbitt(ll x){numm = 1;while(x){if(x%k) return (x%k)*numm;x/=k,numm*=k;}return 0;}
inline ll lowbitv(ll x){numm = 1;while(x){if(x%k) return numm;x/=k,numm*=k;}return 0;}
inline ll get_dep(ll x){depp = 0;while(x%k==0) depp++,x/=k;return depp;}
inline void add(ll x,ll c,ll s,ll t,ll &p){
	if(!p) p=++tr_tot;
	if(s==t){
		tr[p].s ^= c;
		return ;
	}
	if(x<=(s+t)/2) add(x,c,s,(s+t)/2,tr[p].l);
	else add(x,c,(s+t)/2+1,t,tr[p].r);
	tr[p].s = (tr[tr[p].l].s^tr[tr[p].r].s);
} 
inline ll query(ll l,ll r,ll s,ll t,ll p){
	if(!p) return 0;
	if(l<=s&&t<=r) return tr[p].s;
	ll ans = 0;
	if(l<=(s+t)/2) ans^=query(l,r,s,(s+t)/2,tr[p].l);
	if(r>(s+t)/2) ans^=query(l,r,(s+t)/2+1,t,tr[p].r);
	return ans; 
}
int main(){
	n=read(),q=read(),k=read();
	qmi[0] = 1;
	for(i=1;i<=2e5+1;i++) qmi[i]=qmi[i-1]*k;
	vis[0] = -1;
	for(i=1;i<k;i++){
		if(!vis[i]){
			ll temp = 1;
			for(j=i;;j=j*2%k){
				if(j==0){temp=0;break;}
				if(vis[j]==i) break;
				if(vis[j]){temp=0;break;}
				vis[j]=i;
			}
			if(temp){
				tot++;
				x = las = j,head_cir[tot] = (x*2%k),in_head[x*2%k] = 1;
				for(j=x*2%k,numz=1;;j=j*2%k,numz++){
					cir[tot].push_back(j);
					jw[tot] += (j<las);
					len[tot]++;
					jw_cir[j] = jw_cir[las]+(j<las);
					num[j] = numz;
					id_dep[j] = tot;
					in_circle[j] = 1;
					las = j;
					if(j==x) break;
				}
			}
		}
	}
	while(q--){
		op=read();
		if(op==1){
			x=read(),y=read();
			while(!in_circle[lowbit(x)]&&x<=1e9) calc[x]^=y,x+=lowbitt(x);
			if(x>1e9) continue;
			temp = lowbit(x),dep = id_dep[temp],ttt = get_dep(x),ttt2 = ttt,ttt3 = lowbitt(x);
			long long u = (1ll*x-ttt3+1ll*cir[id_dep[temp]][0]*qmi[ttt]-1ll*jw_cir[temp]*qmi[ttt+1]);
			if(!get_id2[id_dep[temp]][u]) get_id2[id_dep[temp]][u]=++id;
			now = get_id2[id_dep[temp]][u];
			add(num[temp],y,0,len[id_dep[temp]],root[now]);
			x = u+1ll*jw[id_dep[temp]]*qmi[ttt+1];
			if(x<=1e9){
				ttt = get_dep(x),ttt2 = get_dep(x);
				dep = id_dep[lowbit(x)];
				x -= lowbitt(x);
				while(ttt--) x/=k;
				x /= k;
				if(!get_id[ttt2][1ll*dep*(1e9+1)+x%jw[dep]]) get_id[ttt2][1ll*dep*(1e9+1)+x%jw[dep]]=++id;
				now = get_id[ttt2][1ll*dep*(1e9+1)+x%jw[dep]];
				add(x,y,0,1e9,root[now]);
			}
		}
		else{
			ans = 0;
			x=read();
			numm = 1,cnt = 0;
			while(x){
				while(x%(numm*k)==0) numm*=k,cnt++;
				temp = (x/numm)%k,ttt = ttt2 = cnt,ttt3 = temp*numm;
				dep = id_dep[temp];
				if(in_circle[temp]){
					ans ^= query(0,num[temp],0,len[dep],root[get_id2[dep][1ll*(x-ttt3+1ll*cir[id_dep[temp]][0]*qmi[ttt]-1ll*jw_cir[temp]*qmi[ttt+1])]]);
					head = (x-ttt3-1ll*jw_cir[temp]*qmi[ttt+1]);
					if(head>=0){
						head /= numm*k;
						ans ^= query(0,head,0,1e9,root[get_id[ttt2][1ll*dep*(1e9+1)+head%jw[dep]]]);
					}
				}
				ans ^= calc[x];
				x -= ttt3;
			}
			write(ans),pc('\n');
		}
	}
	fwrite(obuf,p3-obuf,1,stdout);
	return 0;
}
