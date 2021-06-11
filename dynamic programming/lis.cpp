#include <bits/stdc++.h>
 
#define all(x) x.begin(), x.end()
 
using namespace std;
using ld = long double;
using ll = long long int;
using vi = vector<int>;

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
        return max(x, y);
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
        return ans;
    }
};

int lis(vi& arr) {
    int n = arr.size();
    vi dp(arr.size()), carr(arr);
    
    sort(all(carr));
    carr.resize(unique(all(carr)) - carr.begin());

    FenwickTree fw(carr.size());

    for (int i = 0; i < n; ++i) {
        int idx = lower_bound(all(carr), arr[i]) - carr.begin();
        int bidx = idx - 1; // for strictly increasing
        if (idx < 0) { // no element less than arr[i]
            dp[i] = 1;
        } else {
            dp[i] = fw.get(bidx) + 1;
        }
        fw.update(idx, dp[i]);
    }

    int ans = 1;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[i]);
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    vi arr(n);
    for (int& x : arr) {
        cin >> x;
    }
    cout << lis(arr) << '\n';
}