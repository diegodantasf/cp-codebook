#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#define eq(a, b) (abs(a - b) < EPS)
#define lt(a, b) ((a + EPS) < b)
#define gt(a, b) (a > (b + EPS))
#define le(a, b) (a < (b + EPS))
#define ge(a, b) ((a + EPS) > b)
#define $ ios::sync_with_stdio(0);
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

using ld = long double;
using ll = long long int;
using vi = vector<int>;
using ii = pair<int, int>;

template<class key, class value, class cmp = std::less<key>>
using IndexedMap = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// Have fun
// Read the problem
// Explain the problem with your words to make sure you got it
// Write down information about the problem
// Create a brute force solution