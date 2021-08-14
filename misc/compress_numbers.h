#include <vector>
#include <algorithm>
using namespace std;

struct CompressCoordinates {
    vector<int> cmp;
    CompressCoordinates(vector<int>& arr) {
        cmp = arr;
        sort(all(cmp));
        cmp.resize(unique(all(cmp)) - cmp.begin());
    }
    CompressCoordinates(vector<int>::iterator l, vector<int>::iterator r) {
        cmp = vi(l, r);
        sort(all(cmp));
        cmp.resize(unique(all(cmp)) - cmp.begin());
    }
    int get(int x) {
        return lower_bound(all(cmp), x) - cmp.begin();
    }
    int size() {
        return cmp.size();
    }
};