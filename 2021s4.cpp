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
const int INF = 1e9;
const int N = 2e5;

int n, w, d;
// segm
vi segm(2*N+5, 0);
void build(){
    for(int i = n-1; i > 0; i--){
        segm[i] = min(segm[2*i], segm[2*i+1]);
    }
}
void update(int pos, int val){
    pos += n;
    for(segm[pos] = val; pos > 1; pos/=2){
        segm[pos/2] = min(segm[pos], segm[pos^1]);
    }
}
// interval [l, r)
int query(int l, int r){
    l += n;
    r += n;
    int ret = INF;
    for(l, r; l < r; l/=2, r/=2){
        if(l%2){
            ret = min(ret, segm[l++]);
        }
        if(r%2){
            ret = min(ret, segm[--r]);
        }
    }
    return ret;
}

// dijk
vector<vector<pii>> adjj(n);
vi dist(n);
vi visited(n);
priority_queue<pii> pq;
void dijkstra(int x){
    for(int i = 0; i < n; i++){
        dist[i] = INF;
    }
    dist[x] = 0;
    pq.push({0, x});
    while(!pq.empty()){
        int curr = pq.top().second;
        pq.pop();
        if(visited[curr]){
            continue;
        }
        visited[curr] = true;
        for(pii next : adjj[curr]){
            int ID = next.first;
            int w = next.second;
            if(dist[curr]+w < dist[ID]){
                dist[ID] = dist[curr]+w;
                pq.push({-dist[ID], ID});
            }
        }
    }
}

int main(){
    setIO();
    cin >> n >> w >> d;
    adjj.resize(n+1);
    dist.resize(n+1);
    visited.resize(n+1);
    for(int i = 0; i < w; i++){
        int a, b;
        cin >> a >> b;
        adjj[b].push_back({a, 1});
    }
    // dist & permutation of stations
    dijkstra(n);
    vi pos(n+1, -1);
    vi stations(n);
    for(int i = 0; i < n; i++){
        cin >> stations[i];
        segm[i+n] = i+dist[stations[i]];
        pos[stations[i]] = i;
    }
    build();
    // days
    for(int i = 0; i < d; i++){
        int x, y;
        cin >> x >> y;
        x--; y--;
        // update
        pos[stations[x]] = y;
        pos[stations[y]] = x;
        int temp = stations[x];
        stations[x] = stations[y];
        stations[y] = temp;
        update(x, x+dist[stations[x]]);
        update(y, y+dist[stations[y]]);
        // query
        cout << query(0, pos[n]+1) << "\n";
    }
}
