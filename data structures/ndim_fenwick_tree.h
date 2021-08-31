#include <bits/stdc++.h>
using namespace std;

// D-dimensional Fenwick Tree for RSQ
// O(n^D) memory
// O(log^D(n)) operations
// where D is the number of dimensions

struct ndimFenwickTree {
    int N, Nd;
    vector<int> d, sufd;
    vector<int> fw;

    ndimFenwickTree() : N(0), Nd(0) {}
    ndimFenwickTree(vector<int> dims) {
        Nd = dims.size(); d = dims; 
        N = 1;
        for (int &x : d) N *= x;
        fw = vector<int>(N);

        sufd = vector<int>(Nd + 1, 1);
        for (int i = Nd - 1; i >= 0; --i) {
            sufd[i] = sufd[i + 1] * dims[i];
        }
    }
    int _linearIdx(vector<int>& pos) {
        assert(pos.size() == Nd);
        int idx = 0;
        for (int i = 0; i < Nd; ++i) {
            idx += pos[i] * sufd[i + 1];
        }
        return idx;
    }
    void _add(vector<int>& pos, vector<int>& cur, int delta) {
        int dim = cur.size();
        if (dim == Nd) {
            fw[_linearIdx(cur)] += delta;
            return;
        }
        for (int i = pos[dim]; i < d[dim]; i |= i + 1) {
            cur.push_back(i);
            _add(pos, cur, delta);
            cur.pop_back();
        }
    }
    int _sum(vector<int>& pos, vector<int>& cur) {
        int dim = cur.size();
        if (dim == Nd) {
            return fw[_linearIdx(cur)];
        }
        int ans = 0;
        for (int i = pos[dim]; i >= 0; i = (i & i + 1) - 1) {
            cur.push_back(i);
            ans += _sum(pos, cur);
            cur.pop_back();
        }
        return ans;
    }
    void add(vector<int> pos, int delta) {
        vector<int> cur;
        _add(pos, cur, delta);
    }
    int sum(vector<int> pos) {
        vector<int> cur;
        return _sum(pos, cur);
    }
};