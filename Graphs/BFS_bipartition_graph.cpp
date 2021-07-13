#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <type_traits>
using namespace __gnu_pbds;
using namespace std;

#define all(a) a.begin(), a.end()
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
typedef unsigned long long ull;
int n;
vector<vi> adj;
/**
 * @brief find (a^b)%m in O(log(b))
 * 
 * @param a the base
 * @param b the exponent
 * @param m modullo
 * @return (a^b)%m
 */
ll binpow(ll a, ll b, ll m)
{
    a %= m;
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

/**
 * @brief finds whether the given connected identified by source node is bipartite or not
 * 
 * @param src the source node
 * @param col is the vector denoting the color of the nodes. 
 * If it is -1 no colour is assigned. 
 * 1/0 are the colours used
 * @return true if the connected component including source is bipartitie
 * @return false if the connected component including the source is not bipartite
 */
bool bfs(int src, vector<int> &col)
{
    queue<int> q;
    q.push(src);
    col[src] = 0;
    while (!q.empty())
    {
        int tp = q.front();
        q.pop();
        for (auto nb : adj[tp])
        {
            if (col[nb] == -1)
            {
                col[nb] = 1 ^ col[tp];
                q.push(nb);
            }
            else if (col[nb] == col[tp])
                return 0;
        }
    }
    return 1;
}
/**
 * @brief calculates the number of ways to colur the graph such that it is bipartitie
 * @return int the number of ways to 2-color the graph
 */
int num_bipartitions()
{
    int cmp = 0;
    vector<int> col(n + 1, -1); // -1 means no color is assigned yet
    for (int i = 1; i <= n; i++)
    {
        if (col[i] != -1)
            continue;
        bool poss(bfs(i, col));
        cmp++;
        // if poss is false then the graph is not bipartitie
        if (!poss)
            return 0;
    }
    return binpow(2, cmp, mod);
}
signed main()
{
    int m;
    cin >> n >> m;
    adj.resize(n + 1);
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    cout << num_bipartitions() << endl;
    return 0;
}