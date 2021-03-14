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

vector<vi> edges;
int n, m;

vector<vi> floyd_Warshall(vector<vi> edges, int n, int m)
{
    vector<vi> d(n + 1, vi(n + 1, inf));
    for (int i = 1; i <= n; i++)
    {
        d[i][i] = 0;
    }
    for (auto e : edges)
    {
        d[e[0]][e[1]] = e[2];
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                if (d[i][k] < inf and d[k][j] < inf)
                {
                    d[i][j] = min(d[i][j], d[k][j] + d[i][k]);
                }
            }
    // if a path from i to j has a negative cycle: d[i][j] =-inf

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            for (int x = 1; x <= n; x++)
            {
                // is th possible to reach j from i through x
                //and is the distance from x to itself less than 0
                if (d[i][x] < inf and d[x][j] < inf and d[x][x] < 0)
                {
                    d[i][j] = -inf;
                    break;
                }
            }
        }

    return d;
}
signed main()
{
    return 0;
}