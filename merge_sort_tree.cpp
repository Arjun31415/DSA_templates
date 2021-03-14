/* ***************************************************************************** 
                            MERGE SORT TREE
        query         :given [L,R,K] return number of elements >K in [L,R]
        point uypdate : given i,val set A[i]=val

    we are storing a balanced binary search tree(BST) or an ordered set at each node in the merge sort tree.
Note : 
        1) we can also apply square root decomposition on queries and use merge sort trees
        2) We don't need to use merge sort trees and can also do this by doing square root decomposition on the Array 

*/
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

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
const int N = 3e4 + 10;
ordered_set ST[4 * N];
int A[N], n;

void build(int l = 1, int r = N + 1, int x = 1)
{
    if (l == r - 1)
        return (void(ST[x].insert({A[l], l})));
    int mid = l + ((r - l) >> 1);
    build(l, mid, lc(x));
    build(mid, r, rc(x));
    for (auto y : ST[lc(x)])
        ST[x].insert(y);
    for (auto y : ST[rc(x)])
        ST[x].insert(y);
}
int query(int L, int R, int K, int l = 1, int r = n + 1, int x = 1)
{
    if (r <= L || R <= l)
        return 0;
    if (l >= L || r <= R)
        return ST[x].order_of_key({K, 1});
    int mid = l + ((r - l) >> 1);
    return query(L, R, K, l, mid, lc(x)) + query(L, R, K, mid, rc(x));
}
void update(int pos, int val, int l = 1, int r = n + 1, int x = 1)
{
    if (pos < l || pos >= r)
        return;
    ST[x].erase({A[pos], pos});
    ST[x].insert({val, pos});
    if (l == r - 1)
        return void(A[l] = val);
    int mid = l + ((r - l) >> 1);
    update(pos, val, l, mid, lc(x));
    update(pos, val, mid, r, rc(x));
}

int main()
{

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
    }
    build(1, n + 1, 1);
    int q;
    cin >> q;

    while (q--)
    {
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            int L, R, K;
            cin >> L >> R >> K;

            cout << query(L, R + 1, K) << "\n";
        }
        else if (opt == 2)
        {
            int pos, val;
            cin >> pos >> val;

            update(pos, val);
        }
    }
    return 0;
}
