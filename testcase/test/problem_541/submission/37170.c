#include<stdio.h>
#include<string.h>
#pragma GCC optimize("O3")

int min(int a,int b){
	return a<b?a:b;
}

int read(){
	int x=0;  char ch=0;
	while(ch<'0'||ch>'9')  ch=getchar();
	while(ch>='0'&&ch<='9')  x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}
int T;
int m,a,b,d,i;
int p[2000005];

int _IO_c;
unsigned int seed;
unsigned int randnum(){
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<5;
    return seed;
}

void init_case(){
    int i;
    for(i=1;i<=m;i++){
        if(randnum()%_IO_c==0)p[i]=-1;
        else p[i]=randnum()%b;
    }
}

void update_ans(unsigned int *ans_sum,unsigned int cur_ans,int no){
    const static unsigned int mod=998244353;
    *ans_sum^=(long long)no*(no+7)%mod*cur_ans%mod;
}

int q[2000100],h,t;
int buy[2000100];
int inq[2000100];
int out[2000100],h1,t1;

int main(){
    T=read();
    while(T--){
        unsigned int ans_sum=0,cur_ans=0;
        m=read();scanf("%u%d",&seed,&a);b=read();_IO_c=read();d=read();
        init_case();
        
        if(!d){
        	h=t=h1=t1=0;
			int mins=a+1;
			memset(inq,-1,sizeof(inq));
			memset(buy,0,sizeof(buy));
			for(int i=0;i<=a;++i)
				inq[i]=0,buy[i]=1;
			for(int i=1;i<=m;++i){
				int x=p[i];
				if(x==-1){    
					if(h1==t1)  continue;
					int tmp=out[h1++];
					inq[tmp]=0;
					if(tmp==q[h])  ++h;
				}else if(!buy[x]){    
					buy[x]=1;
					inq[x]=0;
					while(buy[mins])  ++mins;
				}else if(!inq[x]){    
					inq[x]=1;
					out[t1++]=x;
					while(h<t&&q[t-1]>x)  --t;
					q[t++]=x;
				}else{    
					if(h1==t1)  continue;
					int tmp=out[h1++];
					inq[tmp]=0;
					if(tmp==q[h])  h++;
				}
				cur_ans=(h==t?mins:min(mins,q[h]));
		        update_ans(&ans_sum,cur_ans,i);
    		}
		}
        else{
        	int mins=a+1;
			memset(buy,0,sizeof(buy));
			for(int i=0;i<=a;i++)
				buy[i]=1;
			for(int i=1;i<=m;i++){
				int x=p[i];
				if(buy[x]||p[i]==-1)  continue;
				buy[x]=1;
				while(buy[mins])  ++mins;
				cur_ans=mins;
		        update_ans(&ans_sum,cur_ans,i);
		    }
		}
		
        printf("%u\n",ans_sum);
    }
    return 0;
}