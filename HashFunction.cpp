//https://codeforces.com/contest/2149/problem/E
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
// --- START: Custom Hash for unordered_map ---
struct custom_hash {
    // A robust hash function based on SplitMix64
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
// --- END: Custom Hash ---


struct SimpleHash {
    size_t operator()(long long x) const {
        x ^= x >> 16;   // spread bits
        x *= 31;        // multiply by a small prime
        return x;
    }
};

void solve(){
    int  n,k,l,r;
    cin>>n>>k>>l>>r;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    int ans=0;
    int leftk1=0;
    int leftk2=0;
    unordered_map<int,int,SimpleHash>s1;
    unordered_map<int,int,SimpleHash>s2;
    for(int i=0;i<n;i++){
        s1[v[i]]++;
        s2[v[i]]++;
        while(s1.size()>k){
            s1[v[leftk1]]--;
            if(s1[v[leftk1]]==0)s1.erase(v[leftk1]);
            leftk1++;
        }
        while(s2.size()>=k){//maintian s2 of size k-1
            s2[v[leftk2]]--;
            if(s2[v[leftk2]]==0)s2.erase(v[leftk2]);
            leftk2++;
        }
        if(s1.size()==k and s2.size()==k-1){
            int range=min(leftk2-1,i-l+1)-max(leftk1,i-r+1)+1;
            if(range>0)ans+=range;//dont add negative range, see range can get negative 
        }
    }
    cout<<ans<<"\n";
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