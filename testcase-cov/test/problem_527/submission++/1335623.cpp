#include<bits/stdc++.h>
using namespace std;

const int dir[4][2] = {0,1,0,-1,1,0,-1,0};
int N , M , len[1003][1003][4]; bool val[1003][1003][4];
int qry(int p , int q , int f){
	if(len[p][q][f]) return len[p][q][f];
	return len[p][q][f] = (val[p][q][f] ? qry(p + dir[f][0] , q + dir[f][1] , f) + 1 : 0);
}
#define lowbit(x) ((x) & -(x))
int arr[1003];
void add(int x , int v){while(x <= N){arr[x] += v; x += lowbit(x);}}
int qry(int x){int sum = 0; while(x){sum += arr[x]; x -= lowbit(x);} return sum;}

int main(){
	ios::sync_with_stdio(0); cin >> N >> M;
	for(int i = 1 ; i <= N ; ++i) for(int j = 1 ; j < M ; ++j){bool x; cin >> x; val[i][j][0] = val[i][j + 1][1] = x;}
	for(int i = 1 ; i < N ; ++i) for(int j = 1 ; j <= M ; ++j){bool x; cin >> x; val[i][j][2] = val[i + 1][j][3] = x;}
	int ans = 0;
	for(int i = -N + 1 ; i <= M - 1 ; ++i){
		priority_queue < pair < int , int > > q; memset(arr , 0 , sizeof(arr));
		for(int j = N ; j ; --j)
			if(i + j > 0 && i + j <= M){
				int k = i + j , v = min(qry(j , k , 1) , qry(j , k , 3)) , l = min(qry(j , k , 2) , qry(j , k , 0));
				while(q.size() && q.top().first == j){add(q.top().second , -1); q.pop();}
				ans += qry(j + l); q.push(make_pair(j - v - 1 , j)); add(j , 1);
			}
	}
	cout << ans; return 0;
}
