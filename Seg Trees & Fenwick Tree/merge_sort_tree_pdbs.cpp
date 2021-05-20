/* ***************************************************************************** 
                            MERGE SORT TREE
        query         :given [L,R,K] return number of elements >K in [L,R]
        point uypdate : given i,val set A[i]=val

    we are storing a balanced binary search tree(BST) or an ordered set at each node in the merge sort tree.
Note : 
        1) we can also apply square root decomposition on queries and use merge sort trees
        2) We don't need to use merge sort trees and can also do this by doing square root decomposition on the Array 

*/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define lc(x) (x << 1)
#define rc(x) ((x << 1) | 1)
#define pii pair<int, int>
#define all(a) a.begin(), a.end()

#define trace(x) cerr << #x << ": " << x << " " << endl;
typedef tree<pii, null_type, greater<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
const int N = 3e4 + 10;
ordered_set ST[4 * N];
int A[N], n;

void build(int x = 0, int l = 0, int r = n - 1)
{
    if (l == r)
        return (void(ST[x].insert({A[l], l})));
    int mid = l + ((r - l) >> 1);
    build(2 * x + 1, l, mid);
    build(2 * x + 2, mid + 1, r);
    for (auto y : ST[2 * x + 1])
        ST[x].insert(y);
    for (auto y : ST[2 * x + 2])
        ST[x].insert(y);
}
int query(int cur, int l, int r, int x, int y, int k)
{
    if (r < x || l > y)
    {
        return 0; //out of range
    }
    if (x <= l && r <= y)
        // if u are using less<pii> then do ST[cur].order_of_key({k,-1});
        return ST[cur].order_of_key({k, 1e9});
    int mid = l + ((r - l) >> 1);
    return query(2 * cur + 1, l, mid, x, y, k) + query(2 * cur + 2, mid + 1, r, x, y, k);
}
void update(int x, int l, int r, int pos, int val)
{
    if (pos < l || pos > r)
        return;
    ST[x].erase({A[pos], pos});
    ST[x].insert({val, pos});
    if (l == r)
        return void(A[l] = val);
    int mid = l + ((r - l) >> 1);
    update(pos, val, l, mid, 2 * x + 1);
    update(pos, val, mid, r, 2 * x + 2);
}

int main()
{

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    build(0, 0, n - 1);
    int q;
    cin >> q;

    while (q--)
    {
        int opt = 1;
        // cin >> opt;
        if (opt == 1)
        {
            int L, R, K;
            cin >> L >> R >> K;

            cout << query(0, 0, n - 1, L - 1, R - 1, K) << "\n";
        }
        else if (opt == 2)
        {
            int pos, val;
            cin >> pos >> val;

            update(0, 0, n - 1, pos, val);
            // for (auto &x : A)
            //     cerr << x << " ";
            // cerr << "\n";
        }
    }
    return 0;
}
