
#include <bits/stdc++.h>
using namespace std;
#define int long long
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

typedef long long ll;
typedef unsigned long long ull;
namespace BFS
{
    int n, m;
    vector<vi> adj;
    // prints the bfs spanning tree
    void bfs_1(int src, vector<bool> vis = vector<bool>(n + 1, false))
    {
        queue<int> q;
        q.push(src);
        vis[src] = true;
        while (!q.empty())
        {
            int i = q.front();
            q.pop();
            cout << i << " ";
            for (int nb : adj[i])
            {
                if (vis[nb])
                    continue;
                q.push(nb);
                vis[nb] = true;
            }
        }
        cout << "\n";
    }
    // store the minimum distance from src to all other nodes in "dis" vector
    // if we cannot reach a particular node then the distance stored will be -1
    void bfs_2(int src)
    {
        queue<int> q;
        q.push(src);

        vi dis(n + 1, -1);
        dis.at(src) = 0;
        while (!q.empty())
        {
            int i = q.front();
            q.pop();

            for (int nb : adj[i])
            {
                if (dis[nb] != -1)
                    continue;
                q.push(nb);
                dis[nb] = dis[i] + 1;
            }
        }
        REP(i, 1, n + 1)
        {
            cout << i << " " << dis[i] << "\n";
        }
    }
    // get the shortest path from src to dest using BFS spanning tree
    vi get_path(int src, int dest)
    {
        queue<int> q;
        q.push(src);

        vi dis(n + 1, -1);
        vi par(n + 1, -1);
        dis.at(src) = 0;
        while (!q.empty())
        {
            int i = q.front();
            q.pop();

            for (int nb : adj[i])
            {
                if (dis[nb] != -1)
                    continue;
                q.push(nb);
                dis[nb] = dis[i] + 1;
                par[nb] = i;
            }
        }
        if (dis[dest] == -1)
        {
            cout << "NOT REACHABLE\n";
            return vi();
        }
        vi path;
        for (int cur = dest; cur != src; cur = par[cur])
        {
            path.pb(cur);
        }
        path.pb(src);
        reverse(all(path));
        return path;
    }
} // namespace BFS
namespace DFS
{
    //https://github.com/pulkitchhabra6/graphs-sept-21/blob/master/L7/components.cpp
    int n, m;
    vector<vi> adj;

    void dfs(int i, vector<bool> &vis, vector<int> &par)
    {
        vis[i] = 1;
        cout << i << " ";
        for (auto j : adj[i])
        {
            if (!vis[j])
            {
                par[j] = i;
                dfs(j, vis, par);
            }
        }
    }
    // i is the current node
    // vis is the visited array
    // par is the parent array
    // the stack will be having a path to the current node i at all times
    void dfs(int i, vector<bool> &vis, vector<int> &par, stack<int> &s)
    {
        vis[i] = true;
        cout << i << " ";

        // we have path till i in the stack

        s.push(i);
        for (auto j : adj[i])
        {
            if (!vis[j])
            {
                par[j] = i;
                dfs(j, vis, par, s);
            }
        }
        s.pop();
    }
    int components(int n, vector<bool> &vis, vector<int> &par)
    {
        int cc = 0;
        vis.assign(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
                cc++, dfs(i, vis, par);
        }
        return cc;
    }
} // namespace DFS
using namespace BFS;
signed main()
{
    FIO;
    cin >> n >> m;
    adj.resize(n + 1);
    // n nodes and m edges
    while (m--)
    {
        int i, j;
        cin >> i >> j;
        adj[i].pb(j);
        // assuming undirectred
        adj[j].pb(i);
    }
    int u, v;
    cin >> u >> v;
    vi path = get_path(u, v);
    for (auto &i : path)
    {
        cout << i << "->";
    }
    cout << endl;

    return 0;
}