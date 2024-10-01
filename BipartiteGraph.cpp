#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

bool dfs(int cur, vector<vector<int>> &edges, vector<int> &color) {

    int possible = 1;

    for(auto neighbour : edges[cur]) {
        if(color[neighbour] != 0) {
            if(color[neighbour] == color[cur]) {
                possible = false;
            }
        } else {
            color[neighbour] = (color[cur] == 1 ? 2 : 1);
        }
    }

    return possible;
}

signed main() {

	ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<vector<int>> edges(n + 1);

    for(int i = 0; i < m; i++) {
    	int u, v; cin >> u >> v;
    	edges[u].push_back(v);
    	edges[v].push_back(u);
    }

    vector<int> color(n + 1, 0);

    bool possible = 1;

    for(int i = 1; (i <= n) && possible; i++) {
        if(color[i] != 0) continue;
        color[i] = 1;
        possible = possible && dfs(i, edges, color);
    }


    for(auto it : color) cout << it << " ";
    cout << endl;

    
    
}      
