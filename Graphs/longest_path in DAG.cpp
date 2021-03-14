/*
    https://atcoder.jp/contests/dp/tasks/dp_g
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#define ff first
#define ss second
#define int long long
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define pii pair<int, int>
#define vi vector<int>
#define mii map<int, int>
#define pqb priority_queue<int>
#define pqs priority_queue<int, vi, greater<int>>
#define setbits(x) __builtin_popcountll(x)
#define mod 1000000007
#define inf 1e18
#define ps(x, y) fixed << setprecision(y) << x
#define mk(arr, n, type) type *arr = new type[n];
#define range(a, b) substr(a, b - a + 1)
#define w(x)  \
    int x;    \
    cin >> x; \
    while (x--)
#define trace(x) cerr << #x << ": " << x << " " << endl;
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

vector<vi> adj;
int tim = 1;
vi vis_time;
vi dp;
vector<vector<pii>> wt_adj;

int getLargestPath(int i)
{
    if (dp[i] != -1)
        return dp[i];
    dp[i] = 0;
    for (auto e : wt_adj[i])
    {
        int nb = e.ff, w = e.ss;
        dp[i] = max(dp[i], getLargestPath(nb) + w);
    }

    return dp[i];
}
int32_t main()
{
    FIO;
    int n, m;
    cin >> n >> m;
    wt_adj.resize(n + 1);
    while (m--)
    {
        int i, j, w;
        // cin >> i >> j >> w;
        // here the weights were 1
        cin >> i >> j;
        w = 1;
        wt_adj[i].pb({j, w});
    }
    int ans = 0;
    dp.assign(n + 1, -1);
    for (int i = 1; i <= n; ++i)
        ans = max(ans, getLargestPath(i));
    cout << ans;
    return 0;
}