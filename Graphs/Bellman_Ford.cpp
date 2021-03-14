//  solve this https://www.codechef.com/problems/BESTPATH

#include <bits/stdc++.h>

using namespace std;
#define pii pair<int, int>
#define int long long int
#define ff first
#define ss second
#define vi vector<int>
#define pb push_back
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define FOR(i, a, b, c) for (ll i = a; i < b; i += c)
#define inf 1e18
typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;

vector<vi> edges;
// finds the shortest path between souce and every other node in the graph
// src is the source node (1 indexed)
// n is the number of nodes in the graph
// edges array is the adjacency edge list
// if there is a negative cycle one of the d[i] values will be -inf
// to find all such nodes which are affected by negative cycle make it
// FOR(i, 0, 2*n + 1, 1)
vi Bellman_Ford(int src, int n, vector<vi> edges = ::edges)
{
    vi d(n + 1, inf);
    d.at(src) = 0;

    FOR(i, 0, n + 1, 1)
    {
        for (vi &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            if (i <= n - 1)
            {
                if (d[u] < inf)
                {
                    d[v] = min(d[v], d[u] + w);
                }
            }
            else
            {
                if (d[u] + w < d[v])
                {
                    d[v] = -inf;
                }
            }
        }
    }
    return d;
}
// finds a multisource shortest path using Bellman Ford algorithm
// n is the number of nodes in the graph
// edges array is the adjacency edge list
vi multisource_shortest_path(int n)
{

    vi d(n + 1, 0);
    for (int i = 0; i < 2 * n; i++)
    {
        for (vi &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            if (i < n - 1)
            {
                d[v] = min(d[v], d[u] + w);
            }
            else
            {
                if (d[v] > d[u] + w)
                {
                    d[v] = -inf;
                }
            }
        }
    }
    return d;
}

// finds a multisource shortest path using Bellman Ford algorithm
// n is the number of nodes in the graph
// sources is the array of sources from which we wish to find multisource shortest path
// edges array is the adjacency edge list
vi multisource_shortest_path(int n, vi sources)
{

    vi d(n + 1, inf);
    int m = sources.size();
    for (int i = 0; i < m; i++)
    {
        d.at(sources.at(i)) = 0;
    }

    for (int i = 0; i < 2 * n; i++)
    {
        for (vi &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            if (i < n - 1)
            {
                d[v] = min(d[v], d[u] + w);
            }
            else
            {
                if (d[v] > d[u] + w)
                {
                    d[v] = -inf;
                }
            }
        }
    }
    return d;
}

//refer https://cp-algorithms.com/graph/bellman_ford.html
// uses Bellman-Ford algorithm to calculate shortest path and return the shortest path
// Note: negative cycles are not detected
// src is the sorrce node from which the shortest path is calculated
// dest is the destination node where the shortest path ends
// n is the number of nodes in the graph
// edges array is the adjacency edge list
// dist is a refrence to a distance array
// path is refrence to a path array
void path_retrival(int src, int dest, int n, vector<vi> edges = ::edges, vi &dist, vi &path)
{

    vi d(n + 1, inf);
    d.at(src) = 0;
    vector<int> parent(n, -1);
    for (;;)
    {
        bool any = false;
        for (vi &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            if (d[u] < inf) // it means that u is reachable
            {
                if (d[v] > d[u] + w)
                {
                    d[v] = min(d[v], d[u] + w);
                    parent[v] = u;
                    any = true;
                }
            }
        }
        if (any == false)
            break;
    }
    if (d[dest] == inf)
    {
        //cout << "No path from " << src << " to " << dest << "\n";
        path.resize(1);
        path.at(0) = -inf;
        dist = d;
        return;
    }
    else
    {
        path.resize(0);
        path.clear();
        for (int cur = dest; cur != -1; cur = parent[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        dist = d;
        return;

        // cout << "Path from " << v << " to " << t << ": ";
        // for (size_t i = 0; i < path.size(); ++i)
        //     cout << path[i] << ' ';
    }
}
// Bellman_Ford for adjacency list 
// pii- pair of node,weight
void Bellman_Ford(int src, int n, vector<vector<pii>> adj)
{
    vector<float> d(n + 1, inf);
    d.at(src) = 0;
    FOR(i, 1, n, 1)
    {
        FOR(j, 1, n + 1, 1)
        for (auto it = adj[j].begin(); it != adj[j].end(); it++)
        {
            int u = j, v = it->ff;
            float w = it->ss;
            //trace3(u, v, w);
            if (d[u] < inf)
            {
                d[v] = min(d[v], d[u] + w);
            }
        }
    }
    for (int j = 1; j <= n; j++)
    {
        for (auto it = adj[j].begin(); it != adj[j].end(); it++)
        {
            float w = it->ss;
            int v = it->ff;
            // negative cycle found
            if ((d[j] + w) < d[v])
            {
                d[j] = -inf;
            }
        }
    }
}

// reverses the direction of edges in the graph
// edges array is the adjacency edge list
void reverse_graph(vector<vi> &edges)
{
    for (vi &e : edges)
        swap(e[0], e[1]);
}
int main()
{
    //N vertices
    int N;
    cin >> N;
    // M edges
    int M;
    cin >> M;
    for (int i = 0; i < N; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        // edge from u to v with weight w
        edges.pb({u, v, w});
    }
    vi distances = Bellman_Ford(1, N);
    distances = multisource_shortest_path(N);
    return 0;
}