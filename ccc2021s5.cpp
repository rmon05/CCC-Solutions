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

ll lcm(ll x, ll y){
    return x*y/__gcd(x, y);
}

ll n, m;
const ll N = 2e5;
vi segm(2*N+5, 1);
void update(ll l, ll r, ll val){
    l += n;
    r += n;
    for(l, r; l < r; l/=2, r/=2){
        if(l%2){
            segm[l] = lcm(segm[l], val);
            l++;
        }
        if(r%2){
            r--;
            segm[r] = lcm(segm[r], val);
        }
    }
}
ll query(ll pos){
    pos += n;
    ll ret = 1;
    for(pos; pos > 0; pos/=2){
        ret = lcm(ret, segm[pos]);
    }
    return ret;
}

vi segm2(2*N+5, 0);
void build2(){
    for(ll i = n-1; i > 0; i--){
        segm2[i] = __gcd(segm2[2*i], segm2[2*i+1]);
    }
}
void update2(ll pos, ll val){
    pos += n;
    for(segm2[pos] = val; pos > 1; pos/=2){
        segm2[pos/2] = __gcd(segm2[pos], segm2[pos^1]);
    }
}
//[l, r)
ll query2(ll l, ll r){
    l += n;
    r += n;
    ll ret = -1;
    for(l, r; l < r; l/=2, r/=2){
        if(l%2){
            if(ret == -1){
                ret = segm2[l++];
            } else {
                ret = __gcd(ret, segm2[l++]);
            }
        }
        if(r%2){
            if(ret == -1){
                ret = segm2[--r];
            } else {
                ret = __gcd(ret, segm2[--r]);
            }
        }
    }
    return ret;
}


int main(){
    setIO();
    cin >> n >> m;
    vector<pair<pii, ll>> cds;
    for(ll i = 0; i < m; i++){
        ll x, y, z;
        cin >> x >> y >> z;
        x--; y--;
        cds.push_back({{x, y}, z});
        update(x, y+1, z);
    }
    vi a(n);
    for(ll i = 0; i < n; i++){
        a[i] = query(i);
        segm2[i+n] = a[i];
        // test restrictions
        if(a[i] > 1e9){
            cout << "Impossible\n";
            return 0;
        }
    }
    build2();

    // test restrictions
    for(auto p : cds){
        ll x = p.first.first;
        ll y = p.first.second;
        ll z = p.second;
        if(query2(x, y+1) != z){
            cout << "Impossible\n";
            return 0;
        }
    }
    
    for(ll i : a){
        cout << i << " ";
    }
    cout << "\n";
}
