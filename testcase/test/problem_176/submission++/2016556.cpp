#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr ll inf_ll=numeric_limits<ll>::max();
constexpr int max_n=200000;
namespace io{
	constexpr int max_q=200000;
	constexpr int max_len_n=7,max_len_q=7,max_len_x=8,max_len_k=8,max_len_b=20,max_len_ans=20;
	constexpr int input_buf_size=max_len_n+max_len_q+max_n*max_len_k+max_n*max_len_b+max_q*(2+max(max(max_len_x,max_len_n*3),max_len_n+max_len_k+max_len_b));
	constexpr int output_buf_size=max_q*max_len_ans;
	char ibuf[input_buf_size];
	const char*ibufptr;
	char obuf[output_buf_size];
	ll ans[max_q],*ansptr;
	void init(){
		fread(ibuf,1,input_buf_size,stdin),ibufptr=ibuf,ansptr=ans;
	}
	template<typename T>void readuint(T&x){
		const char*ptr=ibufptr;
		x=*ptr^'0';
		for(int ch=*++ptr^'0'; ch<=9; ch=*++ptr^'0')
			x=x*10+ch;
		ibufptr=ptr+1;
	}
	template<typename T>void readint(T&x){
		const char*ptr=ibufptr;
		x=*ptr^'0';
		if(x>9){
			++ibufptr;
			readuint(x);
			x=-x;
			return;
		}
		for(int ch=*++ptr^'0'; ch<=9; ch=*++ptr^'0')
			x=x*10+ch;
		ibufptr=ptr+1;
	}
	template<typename T1,typename T2>void readuint(T1&x,T2&y){
		readuint(x);
		readuint(y);
	}
	template<typename T1,typename T2>void readint(T1&x,T2&y){
		readint(x);
		readint(y);
	}
	void writelnll(const ll&x){
		*ansptr=x;
		++ansptr;
	}
	void flushout(){
		constexpr char*ed=obuf+output_buf_size;
		char*now=ed;
		for(ll*ptr=ansptr,x; --ptr>=ans; ){
			if((x=*ptr)>=0){
				for(*--now='\n'; x>=10; x/=10)
					*--now=(x%10)|'0';
				*--now=x|'0';
			}
			else{
				for(x=-x,*--now='\n'; x>=10; x/=10)
					*--now=(x%10)|'0';
				*--now=x|'0';
				*--now='-';
			}
		}
		fwrite(now,1,ed-now,stdout);
	}
}
struct func{
	ll k,b;
};
func a[max_n+1];
ll dif(const int p,const int q){
	return a[p].k>=a[q].k?inf_ll:((a[p].b-a[q].b)/(a[q].k-a[p].k)+1);
}
ll nowx;
ll getval(const int id){
	return a[id].k*nowx+a[id].b;
}
struct node{
	ll tim;
	int id;
	void pushup(const node&lsn,const node&rsn){
		const int lid=lsn.id,rid=rsn.id;
		const ll lval=getval(lid),rval=getval(rid);
		if(lval>rval)
			id=lid,tim=min(dif(lid,rid),min(lsn.tim,rsn.tim));
		else
			id=rid,tim=min(dif(rid,lid),min(lsn.tim,rsn.tim));
	}
};
node tr[max_n<<1];
void build(const int now,const int lft,const int rgt){
	if(lft==rgt){
		tr[now].tim=inf_ll,tr[now].id=lft;
		return;
	}
	const int mid=(lft+rgt)>>1;
	const int lsn=mid<<1;
	const int rsn=lsn|1;
	build(lsn,lft,mid);
	build(rsn,mid+1,rgt);
	tr[now].pushup(tr[lsn],tr[rsn]);
}
void flsh(const int now,const int lft,const int rgt){
	if(tr[now].tim>nowx)
		return;
	const int mid=(lft+rgt)>>1;
	const int lsn=mid<<1;
	const int rsn=lsn|1;
	flsh(lsn,lft,mid);
	flsh(rsn,mid+1,rgt);
	tr[now].pushup(tr[lsn],tr[rsn]);
}
void update(const int now,const int lft,const int rgt,const int p){
	if(lft==rgt)
		return;
	const int mid=(lft+rgt)>>1;
	const int lsn=mid<<1;
	const int rsn=lsn|1;
	if(p<=mid)
		update(lsn,lft,mid,p),flsh(rsn,mid+1,rgt);
	else
		flsh(lsn,lft,mid),update(rsn,mid+1,rgt,p);
	tr[now].pushup(tr[lsn],tr[rsn]);
}
pair<ll,int>query(const int now,const int lft,const int rgt,const int l,const int r){
	if(l<=lft&&rgt<=r)
		return pair<ll,int>(getval(tr[now].id),tr[now].id);
	const int mid=(lft+rgt)>>1;
	const int lsn=mid<<1;
	const int rsn=lsn|1;
	if(r<=mid)
		return query(lsn,lft,mid,l,r);
	if(l>mid)
		return query(rsn,mid+1,rgt,l,r);
	return max(query(lsn,lft,mid,l,r),query(rsn,mid+1,rgt,l,r));
}
struct note{
	ll val;
	int p,l,r;
	note()=default;
	note(const note&)=default;
	note(const pair<ll,int>&v,const int&x,const int&y):val(v.first),p(v.second),l(x),r(y){
	}
	friend bool operator<(const note&x,const note&y){
		return x.val<y.val;
	}
};
priority_queue<note>pq;
int main(){
	io::init();
	using io::readuint;
	using io::readint;
	int n,q;
	readuint(n,q);
	for(int i=1; i<=n; ++i)
		readint(a[i].k);
	for(int i=1; i<=n; ++i)
		readint(a[i].b);
	nowx=0;
	build(1,1,n);
	for(int op,x,y,z; q; --q){
		readuint(op,x);
		if(op==1){
			nowx+=x;
			continue;
		}
		if(op==2){
			readuint(y,z);
			flsh(1,1,n);
			for(; !pq.empty(); pq.pop());
			pq.emplace(query(1,1,n,x,y),x,y);
			while(--z){
				const note now=pq.top();
				pq.pop();
				if(now.l<now.p)
					pq.emplace(query(1,1,n,now.l,now.p-1),now.l,now.p-1);
				if(now.p<now.r)
					pq.emplace(query(1,1,n,now.p+1,now.r),now.p+1,now.r);
			}
			io::writelnll(pq.top().val);
			continue;
		}
		if(op==3){
			readint(a[x].k,a[x].b);
			a[x].b-=a[x].k*nowx;
			update(1,1,n,x);
			continue;
		}
	}
	io::flushout();
	return 0;
}