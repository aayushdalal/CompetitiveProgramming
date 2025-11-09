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
vector<int>segmentTree;
vector<int>lazytree;
vector<int>v;
int merge(int a,int b){
    return a+b;
}
void build(int l,int r,int index){
    if(l==r){
        segmentTree[index]=v[l];
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,2*index);
    build(mid+1,r,2*index+1);
    segmentTree[index]=merge(segmentTree[2*index],segmentTree[2*index+1]);
}
void update(int l, int r,int index,int ql ,int qr,int value){

    segmentTree[index]+=lazytree[index]*(r-l+1);//resolve the current index
    if(l!=r){
        //propagate if not on child node
        lazytree[2*index]+=lazytree[index];
        lazytree[2*index+1]+=lazytree[index];
    }
    lazytree[index]=0;//resolved for current index

    //complete overlap
    // if(ql<=l and r<=qr){
    //     // you can also do direclty update in the segment tree here dont update in lazy, but when you direclty update here and not in lazy so must propogate value to lazy
    //     lazytree[index]+=value;
    //     return;
    // }

     //complete overlap-> when you directly update in segment tree in complete overlap and not in lazy do this only more safer
    if(ql<=l and r<=qr){
        segmentTree[index] += value * (r - l + 1);
        if (l != r) {
            lazytree[2 * index] += value;// propogate to its lazy child
            lazytree[2 * index + 1] += value;
        }
        return;
    }
    
    
    //no overlap
    if(ql>r or l>qr)return;

    //partial overlap
    int mid=(l+r)/2;
    update(l,mid,2*index,ql,qr,value);
    update(mid+1,r,2*index+1,ql,qr,value);

    segmentTree[index] = merge(segmentTree[2*index], segmentTree[2*index+1]);

}

int query(int l,int r,int index ,int pos){
    //propogate and resolve
    if(lazytree[index]!=0){
        segmentTree[index]+=lazytree[index]*(r-l+1);//resolve the current index
        if(l!=r){
            //propagate if not on child node
            lazytree[2*index]+=lazytree[index];
            lazytree[2*index+1]+=lazytree[index];
        }
        lazytree[index]=0;
    }
    if(l==r)return segmentTree[index];

    int mid=(l+r)/2;
    if(pos<=mid)return query(l,mid,2*index,pos);
    return query(mid+1,r,2*index+1,pos);

}
void solve(){
    int n,q;
    cin>>n>>q;
    v.assign(n,0);
    for(int i=0;i<n;i++)cin>>v[i];
    segmentTree.assign(4*n,0);
    lazytree.assign(4*n,0);
    build(0,n-1,1);
    while(q--){
        int a;
        cin>>a;
        if(a==1){
            int ql,qr,u;
            cin>>ql>>qr>>u;
            update(0,n-1,1,ql-1,qr-1,u);// 0 based indexing
        }else{
            int k;
            cin>>k;
            cout<<query(0,n-1,1,k-1)<<"\n";
        }
    }
}

int32_t main()
{
    fastio;

    int tc = 1;
    // cin >> tc;
    while (tc--)
    {
        solve();
    }
    return 0;
}
