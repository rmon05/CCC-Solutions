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

struct pt{
    ll pos;
    ll w;
    bool start;
    pt(ll p, ll W, ll s){
        pos = p;
        w = W;
        start = s;
    }
};
bool cmp(pt a, pt b){
    return a.pos < b.pos;
}

int main(){
    setIO();
    ll n;
    cin >> n;
    vector<pt> pts;
    for(ll i = 0; i < n; i++){
        ll p, w, d;
        cin >> p >> w >> d;
        pts.push_back(pt(p-d, w, true));
        pts.push_back(pt(p+d, w, false));
    }
    sort(all(pts), cmp);
    // find initial from -INF
    ll amt = 0;
    ll prev = -1e9-5;
    ll sumStartR = 0;
    ll sumEndL = 0;
    for(pt p : pts){
        if(p.start){
            amt += (p.pos-prev)*p.w;
            sumStartR += p.w;
        }
    }
    ll best = amt;
    // iterate
    for(pt p : pts){
        amt -= (p.pos-prev)*sumStartR;
        amt += (p.pos-prev)*sumEndL;
        best = min(best, amt);
        // adjust prev and sums
        prev = p.pos;
        if(p.start){
            sumStartR -= p.w;
        } else {
            sumEndL += p.w;
        }
    }
    cout << best << "\n";
}
