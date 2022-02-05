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

void setIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

struct edge{
    int u, v, c, og;
    edge(int U, int V, int C, int OG){
        u = U; v = V; c = C; og = OG;
    }
};
bool cmp(edge a, edge b){
    if(a.c == b.c){
        return a.og > b.og;
    }
    return a.c < b.c;
}

vi parent;
vi sz;
int find(int node){
    if(parent[node] != node){
        parent[node] = find(parent[node]);
    }
    return parent[node];
}
void merge(int nodeA, int nodeB){
    int repA = find(nodeA);
    int repB = find(nodeB);
    if(sz[repA] > sz[repB]){
        parent[repB] = parent[repA];
        sz[repA] = sz[repA]+sz[repB];
    } else {
        parent[repA] = parent[repB];
        sz[repB] = sz[repA]+sz[repB];
    }
}

int main(){
    setIO();    
    int n, m, d;
    cin >> n >> m >> d;
    vector<edge> edges;
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        if(i < n-1){
            edges.push_back(edge(a, b, c, 1));
        } else {
            edges.push_back(edge(a, b, c, 0));
        }
    }
    //
    for(int i = 0; i < n; i++){
        parent.push_back(i);
        sz.push_back(1);
    }
    // 
    sort(all(edges), cmp);
    // 
    int ans = 0;
    int maxUsed = 0;
    vector<edge> candidates;
    for(edge e : edges){
        if(find(e.u) != find(e.v)){
            maxUsed = max(maxUsed, e.c);
            merge(e.u, e.v);
            if(!e.og){
                ans++;
            }
        } else {
            if(e.c <= d && e.og){
                candidates.push_back(e);
            }
        }
    }
    // replace if able
    if(maxUsed <= d){
        parent.clear();
        sz.clear();
        for(int i = 0; i < n; i++){
            parent.push_back(i);
            sz.push_back(1);
        }
        for(edge e : edges){
            if(e.c == maxUsed && !e.og){
                break;
            }
            if(find(e.u) != find(e.v)){
                merge(e.u, e.v);
            }
        }
        for(edge e : candidates){
            if(find(e.u) != find(e.v)){
                ans--;
                break;
            }
        }
    }
    cout << ans << "\n";
}
