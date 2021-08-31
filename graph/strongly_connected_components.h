// Tarjan’s Algorithm to find Strongly Connected Components
// O(V + E)
// 1-indexed nodes

#include <bits/stdc++.h>
using namespace std;
using graph = vector<vector<int>>;
using ii = pair<int, int>;
const int INF = 0x3f3f3f3f;
class SCC {
private:
    graph gc;
    vector<int> cid, low, pre, stk;
    int tc, cnt;
    void dfs(graph& g, int u) {
        low[u] = pre[u] = tc++;
        stk.push_back(u);
        for (int v : g[u]) {
            if (pre[v] == 0) {
                dfs(g, v);
            }
            low[u] = min(low[u], low[v]);
        }
        if (low[u] == pre[u]) {
            int v;
            do {
                v = stk.back();
                stk.pop_back();
                low[v] = INF;
                cid[v] = cnt;
            } while (v != u);
            ++cnt;
        }
    }
    void buildCompressedGraph(graph& g) {
        gc = graph(cnt);
        set<pair<int, int>> vis;
        for (int u = 1; u < (int)g.size(); ++u) {
            for (int v : g[u]) {
                ii e = {cid[u], cid[v]};
                if (cid[u] != cid[v] && vis.find(e) == vis.end()) {
                    gc[cid[u]].push_back(cid[v]);
                    vis.insert(e);
                }
            }
        }
    }
public:
    SCC(graph& g) {
        low = pre = cid = vector<int>(g.size());
        cnt = tc = 1;
        dfs(g, 1);
        buildCompressedGraph(g);
    }
    graph getCompressedGraph() {
        return gc;
    }
    int getNodeComponent(int u) {
        return cid[u];
    }
    bool sameComponent(int u, int v) {
        return cid[u] == cid[v];
    }
};
