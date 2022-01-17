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
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define epsilon 1e-9
#define sign(x) (x > 0) - (x < 0)
#define is_poweroftwo(n) (n && !(n & (n - 1)))
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

// bfs on trees
// root node
// adjacency list
// n is the number of nodes
void bfs1(int root, vector<vi> &adj, int n)
{
    vi par(n + 1);
    par[root] = 0;
    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        cout << cur << " ";
        for (auto nb : adj[cur])
        {
            if (nb != par[cur])
            {
                q.push(nb);
                par[nb] = cur;
            }
        }
    }
}
// bfs on trees
// root node
// adjacency list
// n is the number of nodes
// prints the nodes accroding to their level from the root.
// Each level is printed in one line
void bfs_level(int root, vector<vi> &adj, int n)
{
    vi par(n + 1);
    par[root] = 0;
    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int cur_sz = q.size();
        // number of nodes currently in the queue
        while (cur_sz--)
        {
            int cur = q.front();
            q.pop();
            cout << cur << " ";
            // ad all the neighbors of cur
            for (int nb : adj[cur])
            {
                if (nb != par[cur])
                {
                    q.push(nb);
                    par[nb] = cur;
                }
            }
        }
        cout << "\n";
    }
}
// bfs level wise on trees
// root node
// adjacency list
// n is the number of nodes
// val is the value of the nodes
// prints the level at which the sum of values of nodes is maximum
long long max_val(int root, vector<vi> &adj, vi &val, int n)
{
    int ans = -1;
    vi par(n + 1);
    par[root] = 0;
    queue<int> q;
    q.push(root);
    int cur_sum = 0;
    while (!q.empty())
    {
        int cur_sz = q.size();
        // number of nodes currently in the queue
        while (cur_sz--)
        {
            int cur = q.front();
            cur_sum = 0;
            q.pop();
            cur_sum += val[cur];
            // ad all the neighbors of cur
            for (int nb : adj[cur])
            {
                if (nb != par[cur])
                {
                    q.push(nb);
                    par[nb] = cur;
                }
            }
        }
        ans = max(ans, cur_sum);
    }
    return ans;
}

int level[10001] = {};
int subtr[10001] = {};
// dfs on trees
//  n is the number of nodes
//  level stores the level of each node with the root being at level 1
//  subtr stores the subtree size for each node
void dfs(int cur, int par, vector<vector<int>> &adj)
{
    cout << cur << " ";
    level[cur] = level[par] + 1;
    for (int nb : adj[cur])
    {
        if (nb == par)
            continue;
        dfs(nb, cur, adj);
        subtr[cur] += subtr[nb];
    }
}
// parent[i][j] stores the 2^j th parent of node i
vector<vi> parent;
vi out, in;
int tim = 0;
int l;
// to assign all the vectors and variables call preprocess()

// ALWAYS CALL parent_calc(root,root,adj);
// DON'T give p=-1 or p=0 else IT WILL MESS UP THE PARENT ARRAY
void parent_calc(int cur, int par, vector<vi> &adj)
{
    parent[cur][0] = par;
    level[cur] = level[par] + 1;
    in[cur] = (++tim);
    for (int i = 1; i <= l; i++)
    {
        int two_i_minus_1 = parent[cur][i - 1];
        parent[cur][i] = parent[two_i_minus_1][i - 1];
    }
    for (auto nb : adj[cur])
        if (nb != par)
            parent_calc(nb, cur, adj);

    out[cur] = ++tim;
}
bool is_first_anc_of_second(int u, int v)
{
    return in[u] <= in[v] && out[u] >= out[v];
}
int find_lca(int u, int v)
{
    if (is_first_anc_of_second(u, v))
        return u;

    if (is_first_anc_of_second(v, u))
        return v;

    for (int i = l; i >= 0; --i)
        if (!is_first_anc_of_second(parent[u][i], v))
            u = parent[u][i];
    return parent[u][0];
}
int d(int u, int v)
{
    return (level[u] + level[v] - 2 * level[find_lca(u, v)]);
}

// root is the root of the tree
// n is the number of nodes
void preprocess(int root, int n, vector<vi> &adj)
{
    in.clear(), in.resize(n);
    out.clear(), out.resize(n);
    tim = 0;
    ::l = ceil(log2(n));
    parent.clear(), parent.assign(n, vector<int>(l + 1));
    dfs(root, root, adj);
}
signed main()
{
    int n;
    FIO;
    cin >> n;
    out.resize(n + 1);
    in.resize(n + 1);
    vector<vi> adj(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1, 0, adj);
    cout << endl;

    return 0;
}