#include<bits/stdc++.h>
using namespace std;
 
int main() {
    int n, m; cin >> n >> m;
 
    vector<vector<int>> adj(n + 1), radj(n + 1);
 
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
 
    vector<int>vis(n + 1), ord;
 
    auto dfs = [&](int node, auto&& self) -> void {
        vis[node] = 1;
        for(auto it : adj[node]) if(!vis[it]) self(it, self);
        ord.push_back(node);
    }; 
 
    for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, dfs);
 
    reverse(ord.begin(), ord.end());
 
    vis.assign(n + 1, 0);
 
    int color = 0;
 
    auto kosaraju = [&](int node, auto &&self) -> void {
        vis[node] = color;
        for(auto it : radj[node]) if(!vis[it]) self(it, self);
    };
 
    for(auto it : ord) {
        if(!vis[it]) {
            color++; kosaraju(it, kosaraju);
        }
    }
 
    cout << color << endl;
 
    for(int i = 1; i <= n; i++) cout << vis[i] << " ";
    cout << endl;
 
}
