#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template <class T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
#define all(a) begin(a), end(a)
#define sort(a) sort(all(a))

void setIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

int main(){
    setIO();
    int g, p;
    cin >> g >> p;
    // planes
    vi a(p);
    for(int i = 0; i < p; i++){
        cin >> a[i];
    }
    // docking
    set<int> left;
    for(int i = 1; i <= g; i++){
	left.insert(i);
    }
    // process
    for(int i = 0; i < p; i++){
	auto grter = left.upper_bound(a[i]);
	if(grter == left.begin()){
	    cout << i << "\n";
	    return 0;
	}
	left.erase(--grter);
    }
    cout << p << "\n";
}
