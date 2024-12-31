#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<int> value(n + 1, 0);

    for(int i = 1; i <= n; i++) cin >> value[i];
    
    vector<vector<int>> adj(n + 1), radj(n + 1), cadj(n + 1);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    vector<int> vis(n + 1), ord, colors(n + 1);

    int color = 0;

    auto dfs = [&](int node, auto &&self) -> void {
        vis[node] = 1;
        for(auto child : adj[node]) if(!vis[child]) self(child, self);
        ord.push_back(node);
    };

    for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, dfs);

    reverse(ord.begin(), ord.end());
    vis.assign(n + 1, 0);

    auto kosaraju= [&](int node, auto &&self) -> void {
        colors[node] = color;
        for(auto child : radj[node]) if(!colors[child]) self(child, self);
    };

    for(auto i : ord) if(!colors[i]) {
        color++;
        kosaraju(i, kosaraju);
    }

    for(int i = 1; i <= n; i++) {
        for(auto child : adj[i]) {
            if(colors[child] != colors[i]) cadj[colors[i]].push_back(colors[child]);
        }
    }
    
    vector<int> sccvalue(n + 1, 0), dp(n + 1, -1);

    for(int i = 1; i <= n; i++) sccvalue[colors[i]] += value[i];

    auto f = [&](int node, auto &&self) -> int {
        if(dp[node] != -1) return dp[node];
        dp[node] = sccvalue[node];
        for(auto child : cadj[node]) {
            dp[node] = max({dp[node], sccvalue[node] + self(child, self)});
        }
        return dp[node];
    };
    
    int ans = 0;
    for(int i = 1; i <= n; i++) ans = max(ans, f(i, f));
    
    cout << ans << endl;
}   
