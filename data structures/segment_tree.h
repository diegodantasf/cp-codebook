#include <vector>
using namespace std;

// Build: O(n)
// Update: point update -- update(pos, x) -- O(log(n))
// Query: range query -- query(i, j) -> combine([i, j]) -- O(log(n))
// 1-indexed
using node = int;
class segTree {
private:	
    vector<node> tr;
    int n, qi, qj;
    node qx;

    node _combine(node l, node r) {
		return l + r;
    }
    void _build(vector<node>& arr, int v, int l, int r) {
        if (l == r) {
            tr[v] = arr[r];
            return;
        }
        int mid = l + r >> 1;
        int vl = v + 1;
        int vr = v + 2 * (mid - l + 1);
        _build(arr, vl, l, mid);
        _build(arr, vr, mid + 1, r);
        tr[v] = _combine(tr[vl], tr[vr]);
    }
    node _query(int v, int l, int r) {
        if (l > qj || r < qi) {
            return node();
        }
        if (l >= qi && r <= qj) {
            return tr[v];
        }
        int mid = l + r >> 1;
        int vl = v + 1;
        int vr = v + 2 * (mid - l + 1);
        return _combine(_query(vl, l, mid), _query(vr, mid + 1, r));
    }
    void _update(int v, int l, int r) {
        if (l > qi || r < qj) {
            return;
        }
        if (l >= qi && r <= qj) {
            tr[v] = qx;
            return;
        }
        int mid = l + r >> 1;
        int vl = v + 1;
        int vr = v + 2 * (mid - l + 1);
        _update(vl, l, mid);
        _update(vr, mid + 1, r);
        tr[v] = _combine(tr[vl], tr[vr]);
    }
public:
	segTree() { }
    void build(vector<node>& arr, int _n) {
        n = _n;
        tr = vector<node>(n << 1);
        _build(arr, 0, 1, n);
    }
    node query(int i, int j) {
        qi = i; qj = j;
        return _query(0, 1, n);
    }
    void update(int i, node x) {
        qi = qj = i; qx = x; 
        _update(0, 1, n);
    }
};
