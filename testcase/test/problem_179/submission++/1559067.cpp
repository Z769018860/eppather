#include<iostream>
#include<cstdio>
using namespace std;
#define ui unsigned int
ui sg2[33][33];bool hv2[33][33];
inline ui mul(ui x,ui y);
inline ui mul1(ui x,ui y)
{
	if((!x)||(!y))return 1<<(x|y);if(hv2[x][y])return sg2[x][y];hv2[x][y]=1;
	ui i,res=1u<<(x^y);for(i=0;i<6;i++)if(x&y&(1u<<i))res=mul(res,3*(1u<<((1u<<i)-1)));return sg2[x][y]=res;
}
inline ui mul(ui x,ui y)
{
	if((x<=1)||(y<=1))return x*y;
	ui i,j,res=0;for(i=0;i<32;i++)if(x&(1u<<i))for(j=0;j<32;j++)if(y&(1u<<j))res^=mul1(i,j);return res;
}
const ui gr=258;
ui nln[65537],nex[65537],m1[65537];
inline ui M3(ui x){return (x>=65535)?(x-65535):x;}
inline ui mul16(ui x,ui y){return ((!x)||(!y))?0:nex[M3(nln[x]+nln[y])];}
inline ui mul32(ui x,ui y)
{
	ui a=mul16(x&65535,y&65535),b=mul16(x>>16,y>>16),c=mul16((x&65535)^(x>>16),(y&65535)^(y>>16));
	return a^((c^a)<<16)^m1[b];
}
ui SA, SB, SC;
ui rng() {
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    ui t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}
ui ans=0;
int main(){
	for(ui i=0;i<5;i++)
	for(ui j=0;j<5;j++)sg2[i][j]=mul1(i,j);
	for(ui i=0,v=1;i<65535;i++){nln[nex[i]=v]=i;v=mul(gr,v);}
	for(ui i=0;i<65536;i++)m1[i]=mul(32768,i);
	int T;
	scanf("%d%u%u%u",&T,&SA,&SB,&SC);
	while(T--)
	{
		ui x = rng() + ans;
		ui y = rng();
		ans = mul32(x, y);
	}
	printf("%u",ans);
	return 0;
}