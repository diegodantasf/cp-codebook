#include <vector>
using namespace std;

// point update & range query O(logn) time
// 0-indexed tree

struct PersistentSegTree {
    // tree stuff
    struct node {
        int ans, vl, vr;
        node() : ans(0), vl(0), vr(0) {}
        node(int ans) : ans(ans), vl(0), vr(0) {}
    };
    int n;
    vector<node> tr;
    vector<int> roots;
    // operational stuff
    int qi, qj;
    node qx; 

    PersistentSegTree(int n) : n(n) {
        roots.push_back(0);
        tr.push_back(node());
    }
    node combine(node vl, node vr) {
        return node(vl.ans + vr.ans);
    }
    void _update(int vOld, int vNew, int l, int r) {
        if (l == r) {
            tr[vNew] = qx;
        } else {
            tr.push_back(node());
            int mid = l + r >> 1;
            if (qi <= mid) { // left child
                tr[vNew].vr = tr[vOld].vr;
                tr[vNew].vl = (int)tr.size() - 1;
                _update(tr[vOld].vl, tr[vNew].vl, l, mid);
            } else { // right child
                tr[vNew].vr =  (int)tr.size() - 1;
                tr[vNew].vl = tr[vOld].vl;
                _update(tr[vOld].vr, tr[vNew].vr, mid + 1, r);
            }
            int vl = tr[vNew].vl;
            int vr = tr[vNew].vr;
            tr[vNew] = combine(tr[vl], tr[vr]);
            tr[vNew].vl = vl;
            tr[vNew].vr = vr;
        }
    }
    node _query(int v, int l, int r) {
        if (l > qj || r < qi) {
            return node();
        }
        if (l >= qi && r <= qj) {
            return tr[v];
        }
        int mid = l + r >> 1;
        return combine(_query(tr[v].vl, l, mid), 
                        _query(tr[v].vr, mid + 1, r));
    }
    void update(int v, int i, int x) {
        qi = i; qx = node(x);
        roots.push_back(tr.size());
        tr.push_back(node());
        _update(roots[v], roots.back(), 0, n - 1);
    }
    node query(int v, int i, int j) {
        qi = i; qj = j;
        return _query(roots[v], 0, n - 1);
    }
};