// FordFulkerson algorithm
// Time complexity: O(E^2 * logV * logF)
// E -> number of edges
// V -> number of nodes
// F -> max flowgit push --set-upstream origin graph/fordFulkerson

#include <bits/stdc++.h>

using namespace std;
using ll = long long int;
using ii = pair<ll, ll>;
const ll INF = 1e17;

class FordFulkerson {
private:
    struct FlowEdge {
        int u, v;
        ll c;
        FlowEdge() {}
        FlowEdge(int _u, int _v, ll _c) 
            : u(_u), v(_v), c(_c) {}
    };
    int n;
    vector<FlowEdge> edges;
    vector<vector<int>> gloc;
    vector<int> par;
    ll maximumBottleneckPath(int s, int t) {
        par = vector<int>(n, -1);
        vector<ll> cost(n);
        priority_queue<ii> pq;
        cost[s] = INF;
        pq.emplace(INF, s);
        while (pq.size()) {
            auto [c, u] = pq.top(); 
            pq.pop();
            if (u == t) {
                return c;
            }
            if (c < cost[u]) {
                continue;
            }
            for (int ei : gloc[u]) {
                int v = u ^ edges[ei].u ^ edges[ei].v;
                ll cb = min(c, edges[ei].c);
                if (cb > cost[v]) {
                    cost[v] = cb;
                    par[v] = ei;
                    pq.emplace(cb, v);
                }
            }
        }
        return 0;
    } 
public:
    FordFulkerson(vector<vector<ii>>& g) {
        n = g.size();
        gloc = vector<vector<int>>(n);
        for (int u = 0; u < n; ++u) {
            for (auto &[v, c] : g[u]) {
                gloc[u].push_back(edges.size());
                gloc[v].push_back(edges.size() + 1);
                edges.emplace_back(u, v, c);
                edges.emplace_back(v, u, 0);
            }
        }
    }
    ll maxFlow(int s, int t) {
        ll ans = 0;
        while (ll flow = maximumBottleneckPath(s, t)) {
            ans += flow;
            for (int ei = par[t]; ei != -1; ei = par[edges[ei].u]) {
                edges[ei].c -= flow;
                edges[ei ^ 1].c += flow;
            }
        }
        return ans;
    }
    // Need to run maxFlow method first
    vector<int> minCutSet(int s) {
        vector<int> ans;
        vector<char> vis(n);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while (q.size()) {
            int u = q.front();
            ans.push_back(u);
            q.pop();
            for (int ei : gloc[u]) {
                int v = u ^ edges[ei].u ^ edges[ei].v;
                if (vis[v] || edges[ei].c == 0) {
                    continue;
                }
                vis[v] = 1;
                q.push(v);
            }
        }
        return ans;
    }
};
