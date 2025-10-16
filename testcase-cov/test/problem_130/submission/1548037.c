#include<stdio.h>
typedef long long ll;
ll n,q,i;
ll s[5000000];
ll tree[5000000];
void build_tree(ll arr[],ll tree[],ll node,ll start,ll end) 
{
    if(start==end)
        tree[node]=arr[start];
    else
    {
        ll mid=(start+end)/2;
        ll left_node = 2*node+1;  
        ll right_node =2 *node+2; 

        build_tree(arr,tree,left_node,start,mid); 
        build_tree(arr,tree,right_node,mid+1,end);
        tree[node]=tree[left_node]+tree[right_node]; 
    }
}
void update_tree(ll arr[],ll tree[],ll node,ll start,ll end,ll idx,ll val)   
{
    if(start==end)
    {
        arr[idx]+=val;  
        tree[node]+=val;
    }
    else
    {
        ll mid=(start+end)/2;
        ll left_node = 2*node+1;
        ll right_node =2 *node+2;
        if(idx>=start&&idx<=mid)
            update_tree(arr,tree,left_node,start,mid,idx,val);
        else
            update_tree(arr,tree,right_node,mid+1,end,idx,val);

        tree[node]=tree[left_node]+tree[right_node];
    }

}
ll query_tree(ll arr[],ll tree[],ll node,ll start,ll end,ll L,ll R) 
{
    if(R<start||L>end)
        return 0;
    else if(L<=start&&end<=R)
        return tree[node];
    else if(start==end)
        return tree[node];
    else
    {
        ll mid=(start+end)/2;
        ll left_node = 2*node+1;
        ll right_node =2 *node+2;
        ll sum_left=query_tree(arr,tree,left_node,start,mid,L,R);
        ll sum_right=query_tree(arr,tree,right_node,mid+1,end,L,R);
        return sum_left+sum_right;
    }

}
int main()
{
    ll a,b,c,sum;
    scanf("%lld %lld",&n,&q);
    for(i=0; i<n; i++)
        scanf("%lld",&s[i]);
    build_tree(s,tree,0,0,n-1);  
    for(i=0; i<q; i++)
    {
        scanf("%lld %lld %lld",&a,&b,&c);
        if(a==1)
            update_tree(s,tree,0,0,n-1,b-1,c);
        else if(a==2)
        {
            sum=query_tree(s,tree,0,0,n-1,b-1,c-1);
            printf("%lld\n",sum);
        }

    }
    return 0;
}
