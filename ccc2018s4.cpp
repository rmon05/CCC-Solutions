#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template <class T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
typedef vector<vector<ll>> vvi;
#define all(a) begin(a), end(a)
#define sort(a) sort(all(a))

void setIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

unordered_map<ll, ll> ans;

ll solve(ll w, ll freq){
    if(w == 1){
        return freq;
    }
    ll denom = w;
    while(denom > 1){
        ll quot = w/denom;
        ll next = w/(quot+1);
        if(!ans[quot]){
            ans[quot] = solve(quot, 1);
        }
        ans[w] += (denom-next)*ans[quot];
        denom = next;
    }
    return freq*ans[w];
}


int main(){
    setIO();    
    ll n;
    cin >> n;
    ans[1] = 1;
    cout << solve(n, 1) << "\n";
}
