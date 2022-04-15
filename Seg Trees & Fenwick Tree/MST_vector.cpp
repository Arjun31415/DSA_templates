/* *****************************************************************************
                            MERGE SORT TREE
        Merge sort tree is 0 indexed and the queries are also 0 indexed
        query         :given [L,R,K] return number of elements >K in [L,R]

    we are storing a sorted vector at each node in the merge sort tree.
Note :
        1) we can also apply square root decomposition on queries and
           use merge sort trees
        2) We don't need to use merge sort trees and can also do this by
           doing square root decomposition on the Array

*/

// Question: https://www.spoj.com/problems/KQUERY/

#include <bits/stdc++.h>
using namespace std;
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
#define int long long
#define FIO                                                                    \
    ios_base::sync_with_stdio(0);                                              \
    cin.tie(0);                                                                \
    cout.tie(0)
const int N = 30000 + 5;
vector<int> tree[4 * N];
int A[N];
void build_tree(int cur, int l, int r)
{
    if (l == r)
    {
        // trace(l);
        tree[cur].push_back(A[l]);
        return;
    }
    int mid = l + (r - l) / 2;
    build_tree(2 * cur + 1, l, mid);     // Build left tree
    build_tree(2 * cur + 2, mid + 1, r); // Build right tree

    merge(all(tree[2 * cur + 1]), all(tree[2 * cur + 2]),
          back_inserter(tree[cur]),
          greater<int>()); // Merging the two sorted arrays
}
/**
 * range of the node cur is [l,r], both inclusive
 * @param cur the current node
 * @param l the left range of the current node
 * @param r the right range of the current ndoe
 * @param x the left bound of query
 * @param y the right bound of query
 * @param k the number for which we are querying
 */
int query(int cur, int l, int r, int x, int y, int k)
{
    if (r < x || l > y)
    {
        return 0; // out of range
    }
    if (x <= l && r <= y)
    {
        // Binary search over the current sorted vector to find elements smaller
        // than K
        //  tracearr(tree[cur]);
        return lower_bound(tree[cur].begin(), tree[cur].end(), k,
                           greater<int>()) -
               tree[cur].begin();
    }
    int mid = l + (r - l) / 2;
    return query(2 * cur + 1, l, mid, x, y, k) +
           query(2 * cur + 2, mid + 1, r, x, y, k);
}

int32_t main()
{
    int n;
    FIO;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    build_tree(0, 0, n - 1);
    int q;
    cin >> q;
    while (q--)
    {
        int opt = 1;
        if (opt == 1)
        {
            int L, R, K;
            cin >> L >> R >> K;
            cout << query(0, 0, n - 1, L - 1, R - 1, K) << "\n";
        }
    }
    return 0;
}
