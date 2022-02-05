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

struct glass{
    ll x, bot, top, tint;
    glass(ll X, ll B, ll T, ll TN){
        x = X; bot = B; top = T; tint = TN;
    }
};
bool cmp(glass a, glass b){
    return a.x < b.x;
}

int main(){
    setIO();    
    ll n, t;
    cin >> n >> t;
    vector<glass> a;
    for(ll i = 0; i < n; i++){
        ll x1, y1, x2, y2, tint;
        cin >> x1 >> y1 >> x2 >> y2 >> tint;
        a.push_back(glass(x1, y1, y2, tint));
        a.push_back(glass(x2, y1, y2, -tint));
    }
    sort(all(a), cmp);
    //
    ll ans = 0;
    set<ll> y; 
    unordered_map<ll, ll> tintChange;
    unordered_map<ll, ll> yFreq;
    ll prevX = -1;
    for(ll i = 0; i < a.size(); i++){
        auto curr = a[i];
        // process and add to ans
        if(i){
            ll tint = 0;
            ll prevY = -1;
            ll sum = 0;
            for(auto yy : y){
                if(prevY != -1 && tint >= t){
                    sum += yy-prevY;
                }
                // update
                tint += tintChange[yy];
                prevY = yy;
            }
            ans += sum*(curr.x-prevX);
        }
        // update
        prevX = curr.x;
        if(curr.tint > 0){
            // add a glass
            bool botIn = false;
            bool topIn = false;
            for(auto yy : y){
                if(yy == curr.bot){
                    tintChange[yy] += curr.tint;
                    botIn = true;
                }
                if(yy == curr.top){
                    tintChange[yy] -= curr.tint;
                    topIn = true;
                }
            }   
            if(!botIn){
                y.insert(curr.bot);
                tintChange[curr.bot] = curr.tint;
            }
            if(!topIn){
                y.insert(curr.top);
                tintChange[curr.top] = -curr.tint;
            }
            yFreq[curr.bot]++;
            yFreq[curr.top]++;
        } else {
            // remove a glass
            tintChange[curr.bot] += curr.tint;
            tintChange[curr.top] -= curr.tint;
            yFreq[curr.bot]--;
            yFreq[curr.top]--;
            if(!yFreq[curr.bot]){
                y.erase(curr.bot);
            } 
            if(!yFreq[curr.top]){
                y.erase(curr.top);
            }            
        }
    }
    cout << ans << "\n";
}

