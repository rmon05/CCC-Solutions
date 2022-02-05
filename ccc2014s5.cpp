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

void setIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

struct edge{
    ll a, b, w;
    edge(ll A, ll B, ll W){
        a = A; b = B; w = W;
    }
};
bool cmp(edge a, edge b){
    return a.w < b.w;
}

int main(){
    setIO();    
    ll n;
    cin >> n;
    vector<pii> a(n);
    for(ll i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    vector<edge> edges;
    vvi weights(n, vi(1, -1));
    for(ll i = 0; i < n; i++){
        for(ll j = i+1; j < n; j++){
            ll x = (a[i].first-a[j].first)*(a[i].first-a[j].first);
            ll y = (a[i].second-a[j].second)*(a[i].second-a[j].second);
            edges.push_back(edge(i, j, x+y));
        }
    }
    sort(all(edges), cmp);
    for(edge e : edges){
        if(weights[e.a].back() != e.w){
            weights[e.a].push_back(e.w);
        }
        if(weights[e.b].back() != e.w){
            weights[e.b].push_back(e.w);
        }
    }
    for(ll i = 0; i < n; i++){
        sort(all(weights[i]));
    }
    //
    vvi dp(n, vi(n+1, 1));
    for(edge e : edges){
        ll posA = lower_bound(all(weights[e.a]), e.w)-weights[e.a].begin();
        ll posB = lower_bound(all(weights[e.b]), e.w)-weights[e.b].begin();
        // dp for a
        dp[e.a][posA] = max(dp[e.a][posA], dp[e.a][posA-1]);
        dp[e.a][posA] = max(dp[e.a][posA], dp[e.b][posB-1]+1);        
        // dp for b
        dp[e.b][posB] = max(dp[e.b][posB], dp[e.b][posB-1]);
        dp[e.b][posB] = max(dp[e.b][posB], dp[e.a][posA-1]+1);
    }
    // 
    ll ans = 1;
    for(ll i = 0; i < n; i++){
        ll distO = a[i].first*a[i].first+a[i].second*a[i].second;
        ll pos = lower_bound(all(weights[i]), distO)-weights[i].begin()-1;
        ans = max(ans, dp[i][pos]);
    }
    cout << ans << "\n";
}

