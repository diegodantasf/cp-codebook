// Kuhn's algorithm maximum matching in bipartide graphs
// Time complexity O(V * E)
// Note: Heuristics can make it fast on random graphs

#include <bits/stdc++.h>

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using ii = pair<int, int>;

class Kuhn {
private:
    int k, epoch;
    vector<vector<int>> g;
    vector<int> skip, vis;
    bool dfs(int u) {
        vis[u] = epoch;
        for (int v : g[u]) if (vis[skip[v]] != epoch) {
            if (skip[v] == -1 || dfs(skip[v])) {
                skip[v] = u;
                return true;
            }
        }
        return false;
    }
public:
    // graph g expected to:
    // g[:k] first partition
    // g[k:] second partition
    Kuhn(vector<vector<int>>& _g, int _k) :  k(_k), g(_g) {
        epoch = 1;
        skip.assign(g.size(), -1);
        vis.assign(g.size(), 0);
        // Heuristics time!
        // Heuristic #1 - Shuffle adjancecy list
        for (int u = k; u < (int)g.size(); ++u) {
            shuffle(g[u].begin(), g[u].end(), rng);
        }
        // Heuristic #2 - Warm start
        for (int u = 0; u < k; ++u) {
            for (int v : g[u]) {
                if (vis[v] == epoch) {
                    vis[v] = epoch;
                    skip[v] = u;
                    break;
                }
            }
        }
    }
    vector<ii> maximumMatching() {
        for (int u = 0; u < k; ++u) {
            ++epoch;
            if (skip[u] == -1) { //not satured
                dfs(u);
            }
        }
        vector<ii> ans;
        for (int u = k; u < (int)g.size(); ++u) {
            if (skip[u] != -1) {
                ans.emplace_back(skip[u], u);
            }
        }
        return ans;
    }   
};