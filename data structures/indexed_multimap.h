#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 

using namespace __gnu_pbds;
using namespace std;

template<class key, class value, class cmp = std::less<key>>
using IndexedMap = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<class key, class value> 
struct IndexedMultimap {  
    int tc;
    IndexedMap<pair<key, int>, value> imp;
    
    IndexedMultimap() : tc(0) {}
    void insert(key x) {
        imp.insert({x, tc++});
    }
    void erase(key x) {
        imp.erase(imp.lower_bound({x, -1}));
    }
    key find_by_order(int i) {
        return imp.find_by_order(i)->first;
    }
    int order_of_key(key x) {
        return imp.order_of_key({x, -1});
    }
};