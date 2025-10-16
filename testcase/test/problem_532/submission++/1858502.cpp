#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e6+5;
const int MOD=1e9+7;
int a[MAXN];
int A,B,C;
long long L1,L2,R1,R2;
int vis[MAXN];
int Cnt1[MAXN];
int Cnt2[MAXN];
int Sum1[MAXN];
int Sum2[MAXN];
signed main()
{
    
    
    scanf("%lld %lld %lld %lld %lld %lld %lld %lld",&A,&B,&C,&a[0],&L1,&R1,&L2,&R2);
    int st,ed;
    for(int i=1;i<=C;i++)
    {
        vis[i]=-1;
    }
    vis[a[0]]=0;
    for(int i=1;;i++)
    {
        a[i]=((long long)a[i-1]*A+B)%C+1;
        if(vis[a[i]]!=-1)
        {
            st=vis[a[i]];
            ed=i-1;
            break;
        }
        else
        {
            vis[a[i]]=i;
        }
    }
    
    for(int i=1;i<=C;i++)
    {
        if(vis[i]==-1)
        {
            Cnt1[i]=Cnt2[i]=0;
        }
        else
        {
            int Pos=vis[i];
            if(Pos>=st&&Pos<=ed)
            {
                int Len=ed-st+1;
                Pos-=(st-1);
                int l1=max(0ll, L1-(st-1));
                int r1=max(0ll, R1-(st-1));
                int l2=max(0ll, L2-(st-1));
                int r2=max(0ll, R2-(st-1));
                
                Cnt1[i]=((r1/Len+(((r1%Len)?(r1%Len):0)>=Pos))-((l1-1)/Len+((((l1-1)%Len)?((l1-1)%Len):0)>=Pos)));
                Cnt2[i]=((r2/Len+(((r2%Len)?(r2%Len):0)>=Pos))-((l2-1)/Len+((((l2-1)%Len)?((l2-1)%Len):0)>=Pos)));
            }
            else
            {
                if(Pos>=L1)
                {
                    Cnt1[i]=1;
                }
                else
                {
                    Cnt1[i]=0;
                }

                if(Pos>=L2)
                {
                    Cnt2[i]=1;
                }
                else
                {
                    Cnt2[i]=0;
                }
            }
        }
    }
    for(int i=1;i<=C;i++)
    {
        (Cnt1[i])%=MOD;
        (Cnt2[i])%=MOD;
        Sum1[i]=(Sum1[i-1]+(Cnt1[i])%MOD)%MOD;
        Sum2[i]=(Sum2[i-1]+(Cnt2[i])%MOD)%MOD;
        
    }
    int Res=0;
    for(int i=1;i<=C;i++)
    {
        Res=((long long)Res+(2ll*Cnt1[i]*Cnt2[i])%MOD);
        for(int k=3, Last = i;k<=(C)+1;k++)
        {
            
            int Cf=min(C, (int)floor(i*(k+sqrt(k*k-4))/2));
            Res=((long long)Res+(((((long long)(Sum2[Cf]-Sum2[Last] + MOD) % MOD)*(Cnt1[i]))%MOD)*k)%MOD)%MOD;
            Res=((long long)Res+(((((long long)(Sum1[Cf]-Sum1[Last] + MOD) % MOD)*(Cnt2[i]))%MOD)*k)%MOD)%MOD;
            Last=Cf;
            if (Cf >= C) break;
        }
        
    }
    printf("%lld\n",(Res));
    
}