#include <iostream>
#include <vector>
using namespace std;
namespace adjacency_matrix
{
    const int N = 100;
    // We are storing N^2 elements always.
    // a lot of times, N ~ 1e5, M ~ 2e5
    int G[N][N];
    int n, m;
    void ReadGraph()
    {
        // n = number of nodes, m = number of edges.
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            // m lines, each containing an edge (x, y).
            int x, y;
            cin >> x >> y;
            G[x][y] = 1;
            G[y][x] = 1;
        }
    }
    vector<int> GetAllNeighboursOfANode(int x)
    {
        // O(N) time instead of O(deg(x)).
        vector<int> ret;
        for (int i = 1; i <= n; i++)
        {
            if (G[x][i])
            {
                ret.push_back(i);
            }
        }
        return ret;
    }

    int is_adjacent(int x, int y)
    {
        // return true if there exists an edge between x & y.
        // O(1) to check adjacency of two vertices.
        return G[x][y];
    }

} // namespace adjacency_matrix
namespace adjacency_list
{
    const int N = 1e5 + 10;
    const int M = 1e6 + 10;
    vector<int> g[N];
    int n, m;
    void ReadGraph()
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
    }
    vector<int> GetAllNeighboursOfANode(int x)
    {
        // O(deg(x)) time.
        return g[x];
    }
    int is_adjacent(int x, int y)
    {
        // return true if there exists an edge between x & y.
        // Spending O(deg(x))
        for (auto w : g[x])
        {
            //   for(int i = 1; i <= g[x].size(); i++){ int w = g[x][i];
            if (w == y)
            {
                return 1;
            }
        }
        return 0;
    }
} // namespace adjacency_list

namespace edge_list
{
    const int N = 1e5 + 10;
    const int M = 1e6 + 10;
    int U[M], V[M], W[M];
    // i'th edge will be between vertices U[i] and V[i]. The weight of the i'th edge
    // will be W[i].
    vector<int> g[N];
    int n, m;
    int adj(int x, int e)
    {
        // Takes a node x and an edge number e which is adjacent to the node x.
        // Returns the opposite vertex of x along edge e.
        return U[e] ^ V[e] ^ x;
        //   if (U[e] == x) {
        //     return V[e];
        //   } else if (V[e] == x) {
        //     return U[e];
        //   }
    }
    void ReadGraph()
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            // int x, y;
            // cin >> x >> y;
            // ordering is same as the order in which they appear in the input.
            cin >> U[i] >> V[i] >> W[i];
            g[U[i]].push_back(i);
            g[V[i]].push_back(i);
        }
    }
    vector<int> GetAllNeighboursOfANode(int x)
    {
        vector<int> ret;
        for (auto e : g[x])
        {
            ret.push_back(adj(x, e));
        }
        return ret;
    }
    bool is_adjacent(int x, int y)
    {
        for (auto e : g[x])
        {
            if (adj(x, e) == y)
            {
                return true;
            }
        }
        return false;
    }
} // namespace edge_list

int main()
{
    int n;
    return 0;
}
