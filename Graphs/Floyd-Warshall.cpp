#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define int long long int
#define vi vector<int>
#define pb push_back
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define FOR(i, a, b, c) for (ll i = a; i < b; i += c)
#define inf 1e18
typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;

vector<vi> edges, d;
int n, m;

/**e

 * @brief finds all pair shortest path between the nodes present in the graph.
 * If the two nodes are not reachable then d[i][j]=inf and if there is a negative cycle between them
 * d[i][j] = -inf
 * @param edges edges is the edge list stored as {u,v,w}. i.e edge from u->v with weight w
 * @param n n is number of vertices
 * @param m m is the number of edges;
 * @param d the matrix in which the distance is to be stored
 */
void floyd_Warshall(vector<vi> edges, int n, int m, vector<vi> &d = ::d)
{
    d = vector<vi>(n + 1, vi(n + 1, inf));
    for (int i = 1; i <= n; i++)
    {
        d[i][i] = 0;
    }
    for (auto e : edges)
    {
        d[e[0]][e[1]] = min(d[e[0]][e[1]], e[2]);
    }
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                if (d[i][k] < inf and d[k][j] < inf)
                {
                    d[i][j] = min(d[i][j], d[k][j] + d[i][k]);
                }
            }
        for (int i = 1; i <= n; i++, cout << "\n")
            for (int j = 1; j <= n; j++)
            {
                cout << (d[i][j] == inf ? -1 : d[i][j]) << " ";
            }
        cout << "\n\n";
    }
    // if a path from i to j has a negative cycle: d[i][j] =-inf

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            for (int x = 1; x <= n; x++)
            {
                // is th possible to reach j from i through x
                // and is the distance from x to itself less than 0
                if (d[i][x] < inf and d[x][j] < inf and d[x][x] < 0)
                {
                    d[i][j] = -inf;
                    break;
                }
            }
        }

    return;
}
signed main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.pb({u, v, w});
        edges.pb({v, u, w});
    }
    floyd_Warshall(edges, n, m);
    return 0;
}