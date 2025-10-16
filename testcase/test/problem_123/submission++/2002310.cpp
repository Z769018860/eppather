#include <bits/stdc++.h>
using namespace std;
struct edge{
	int from,to,value;
}e[500005];
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read(){
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57){
        if(ch=='-')f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57){
        x=x*10+ch-48;
		ch=nc();
    }
   	return x*f;
}
int n,m,u,v,w,f[200005];
long long ans=0;
int find(int k){
	if(f[k]==k)return k;
	return f[k]=find(f[k]);
}
bool cmp(edge a,edge b){
	return a.value<b.value;
}
void kruskal(){
	for(int i=1;i<=m;i++){
		if(find(e[i].from)!=find(e[i].to)){
			ans+=e[i].value;
			f[find(e[i].from)]=find(e[i].to);
		}
	}
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		u=read();
		v=read();
		w=read();
		e[i].from=u;
		e[i].to=v;
		e[i].value=w;
	}
	sort(e+1,e+m+1,cmp);
	kruskal();
	cout<<ans;
}