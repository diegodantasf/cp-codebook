// Update: point update -- update(pos, x)
// Query: prefix queries -- get(pos) -> f([0, pos])
// Time: O(log(n))
struct FenwickTree{
    vector<int> fw;
    FenwickTree(int n) {
        fw = vector<int>(n);
    }
    
    // Change depending on the application
    inline int zero() {
        return 0;
    }
    inline int f(int x, int y) {
        return x + y;
    }

    void update(int pos, int x) {
        for (; pos < (int)fw.size(); pos |= pos + 1) {
            fw[pos] = f(fw[pos], x);
        }
    }
    int get(int pos) {
        int ans = zero();
        for (; pos >= 0; pos = (pos & pos + 1) - 1) {
            ans = f(ans, fw[pos]);
        }   
    }
};