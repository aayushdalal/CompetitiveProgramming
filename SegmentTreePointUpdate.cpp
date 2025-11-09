#include <bits/stdc++.h>
using namespace std;

#define fastio std::ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MOD 1000000007
#define int long long

// Compiler optimization directives

// Fast I/O setup
static const auto harsh = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
vector<int>SegmentTree;
vector<int>v;
int merge(int a,int b){
    return min(a,b);// for query asking minimum, for sum return a+b
}
void buildtree(int l,int r,int index){
    if(l==r){
        SegmentTree[index]=v[l];
        return;
    }
    int mid=(l+r)/2;
    buildtree(l,mid,2*index);
    buildtree(mid+1,r,2*index+1);
    SegmentTree[index]=merge(SegmentTree[2*index],SegmentTree[2*index+1]);
    return; 
}
void update(int l,int r,int index,int pos,int val){
    if(l==r){//it is guranted that when this condition comes we have pos==l==r
        SegmentTree[index]=val;
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid){//go left ,equal to here is necessary because we have range 1 to mid and pos==mid so its in left 
        update(l,mid,2*index, pos, val);
    }
    else{ //else go right
        update(mid+1,r,2*index+1,pos,val);
    }
    SegmentTree[index]=merge(SegmentTree[2*index],SegmentTree[2*index+1]);// simple update the path from which we came
}
int query(int l,int r,int index,int ql,int qr){
    if(ql<=l and r<=qr){
        return SegmentTree[index];//return the complete segment sum
    }
    if(ql>r or qr<l)return 1e18;// no sum will exsist in this range, return the default value according to need , is asked min query instead of sum query then dont return 0 but return 1e18
    int mid=(l+r)/2;
    int a=query(l,mid,2*index,ql,qr);//left childt at 2*index
    int b=query(mid+1,r,2*index+1,ql,qr);//right child at 2*index +1
    return merge(a,b);// its the min of a,b, min of a range 
}
void solve(){
    int n;
    cin>>n;
    v.resize(n);
    for(int i=0;i<n;i++)cin>>v[i];
    SegmentTree.assign(4*n,0);//segment tree array, dont do resize do assing
    buildtree(0,n-1,1);// pass l to r and tree index ,  index starts at 0
    int i,x;
    cin>>i>>x;
    update(0,n-1,1,i,x);// 0 ,n-1 is the starting range , 1 is the root index these three will always remain same, then we have index to update and the value to be update with
    int ql,qr;
    cin>>ql>>qr;
    cout<<query(0,n-1,1,ql,qr);
}

int32_t main()
{
    fastio;

    int tc = 1;
    cin >> tc;
    while (tc--)
    {
        solve();
    }
    return 0;
}
