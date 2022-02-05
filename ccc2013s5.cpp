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

const ll N = 5e6+5;
vector<bool> isPrime(N+1, true);
vi primes;
void sieve(){
    for(ll p = 2; p*p <= N; p++){
        if(!isPrime[p]){
            continue;
        }
        for(ll i = p*p; i <= N; i+=p){
            isPrime[i] = false;
        }
    }
    for(ll p = 2; p <= N; p++){
        if(isPrime[p]){
            primes.push_back(p);
        }
    }
}


int main(){
    setIO();
    sieve();
    ll n;
    cin >> n;
    //
    ll x = 1e2;
    vi dp(x+5, 1e18);
    dp[1] = 0;
    for(ll i = 1; i < x; i++){
        for(ll j = 1; j*j <= i; j++){
            if(i%j){
                continue;
            }
            if(i+i/j <= x){
                dp[i+i/j] = min(dp[i+i/j], dp[i]+j);
            }
            if(i+j <= x){
                dp[i+j] = min(dp[i+j], dp[i]+i/j);
            }
        }
    }
    //
    ll ans = 0;
    while(n > x){
        for(ll p : primes){
            if(n%p == 0){
                ans += p-1;
                n = (n/p)*(p-1);
                break;
            }
        }
    }
    cout << ans+dp[n] << "\n";
}
