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

// --- Simple and reliable custom hash for unordered_map/unordered_set ---
struct SimpleHash {
    size_t operator()(long long x) const {
        x ^= x >> 16;
        x *= 31;
        return x;
    }
};
// Usage example: unordered_map<int,int,SimpleHash> mp;
vector<int>SegmentTree;
long long merge(long long a,long long b){
    return a+b;
}
void build(int l,int r,int index){// l ,r denotes the sum

}
void update(int l,int r,int index,int pos){
    if(l>pos or r<pos)return ; //always write this at top else if l==r and even its not in range we will update segment tree[index] which will cause so many problems
    if(l==r){
        SegmentTree[index]++;
        return;
    }
    int mid=(l+r)/2;
    update(l,mid,2*index,pos);
    update(mid+1,r,2*index+1,pos);
    SegmentTree[index]=merge(SegmentTree[2*index],SegmentTree[2*index+1]);
}
// so either return early or use below code, call the recrusive only when its in range

// void update(int l,int r,int index,int pos){
//     if(l==r){
//         SegmentTree[index]++;
//         return;
//     }
//     if(l>pos or r<pos)return ;
//     int mid=(l+r)/2;
//     if (pos <= mid) {
//         // Position is in the left child's range
//         update(l, mid, 2 * index, pos);
//     } else {
//         // Position is in the right child's range
//         update(mid + 1, r, 2 * index + 1, pos);
//     }
//     SegmentTree[index]=merge(SegmentTree[2*index],SegmentTree[2*index+1]);
// }
long long query(int l,int r,int index,int ql,int qr){
    if(ql<=l and qr>=r){
        return SegmentTree[index];
    }
    if(ql>r or qr<l)return 0;

    int mid=(l+r)/2;
    int a=query(l,mid,2*index,ql,qr);
    int b=query(mid+1,r,2*index+1,ql,qr);
    return merge(a,b);
    // SegmentTree[index]=merge(SegmentTree[2*index],SegmentTree[2*index+1]);
}
long long countMajoritySubarrays(vector<int>& nums, int target) {
    for(int &a:nums){
        if(a==target)a=1;
        else a=-1;
    }
    for(int i=1;i<nums.size();i++){
        nums[i]+=nums[i-1];//prefixwsum
    }
    int n=nums.size();// max possible sum possible when all elements equal to target, so our range of elements is 0 to 2*n+1, because we can have -n sum also
    SegmentTree.assign(4*(2*n+1)+1,0);
    //initially only when sum=0 is set to 1 ,so index at segment tree at 0+n= n the leaf is 1
    // SegmentTree[n]=1;//l==n r==n, that is prefixsum=0
    update(0,2*n,1,n);//use update function never do segment tree[n], here we are not updating nth index of segment tree, we are updating the loigcal range of prefixusm=0 ,range is -n to n so we shift by n its 0 to 2*n so we update at nth value(pos) not literally the nth index of segment tree
    long long ans=0;
    for(int i=0;i<n;i++){
        ans+=query(0,2*n,1,0,n+nums[i]-1);// find the count of prefixsum in range 0 to n+nums[i]-1
        update(0,2*n,1,n+nums[i]);// update the freqcount of curr prefixsum , that is at n+nums[i] index
    }
    return ans;

}


void solve(){
    
}

int32_t main()
{
    fastio;

//#ifndef ONLINE_JUDGE
//freopen("input.txt", "r", stdin);
//freopen("output.txt", "w", stdout);
//#endif
    int tc = 1;
    cin >> tc;
    while (tc--)
    {
        solve();
    }
    return 0;
}
