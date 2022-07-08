// Accepted code for https://acm.timus.ru/problem.aspx?space=1&num=1471

// TO solve - https://codeforces.com/contest/342/problem/E
//  Read -
// 1. https://tanujkhattar.wordpress.com/2016/01/10/centroid-decomposition-of-a-tree/
// 2. https://usaco.guide/plat/centroid?lang=cpp

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
const int LOGN = 20;
// Original Tree
vector<int> g[N];
//  edge from U[i] to V[i] with weight W[i] having edge number i
// deleted[i] marks edge i as deleted
// nn is number of nodes in the component
int sub[N], nn, U[N], V[N], W[N], deleted[N];
// Centroid Tree
int par[N], level[N], dist[LOGN][N];
// dist[LOGN][N] : dist[lvl][x] :  Distance between C and x in the original tree, when node C becomes a centroid at level "lvl".
// G[u] --> [v1, v2, v3] ... Not doing this.
// G[u] --> [e1, e1, e3 ..]
int adj(int x, int e) { return U[e] ^ V[e] ^ x; }
void dfs1(int u, int p)
{
    sub[u] = 1;
    nn++;
    for (auto e : g[u])
    {
        int w = adj(u, e);
        if (w != p && !deleted[e])
            dfs1(w, u), sub[u] += sub[w];
    }
}
int find_centroid(int u, int p)
{
    for (auto e : g[u])
    {
        if (deleted[e])
            continue;
        int w = adj(u, e);
        if (w != p && sub[w] > nn / 2)
            return find_centroid(w, u);
    }
    return u;
}
void add_edge_centroid_tree(int parent, int child)
{
    par[child] = parent;
    level[child] = (parent != -1) ? level[parent] + 1 : 1;
}
void dfs2(int u, int p, int lvl)
{
    for (auto e : g[u])
    {
        int w = adj(u, e);
        if (w == p || deleted[e])
            continue;
        dist[lvl][w] = dist[lvl][u] + W[e];
        dfs2(w, u, lvl);
    }
}
// unordered_map<int, int> dist[N]; -- inefficient.
// all the nn nodes which lie in the component of "centroid"
// dist[centroid][x] = <value>
// int dist[LOGN][N]; (centroid,x) --> one to one mapping --> (level[centroid], x);
void decompose(int root, int p = -1)
{
    nn = 0;
    // Compute subtree sizes and no. of nodes (nn) in this tree.
    dfs1(root, root);
    // Find the centroid of the tree and make it the new root.
    int centroid = find_centroid(root, root);
    // Construct the Centroid Tree
    // if (p == -1)
    //     p = centroid;
    add_edge_centroid_tree(p, centroid);
    // Process the O(N) paths from centroid to all leaves in this component.
    dfs2(centroid, centroid, level[centroid]);
    // Delete the adjacent edges and recursively decompose the adjacent subtrees.
    for (auto e : g[centroid])
    {
        if (deleted[e])
            continue;
        deleted[e] = 1;
        int w = adj(centroid, e);
        decompose(w, centroid);
    }
}

int compute_distance(int x, int y)
{
    // We need to compute the LCA(x, y) in the centroid tree.
    // O(logN) by just manual iteration because
    // height of centroid tree is O(logN)

    // if binary jumping is used it becomes O(log(logN))
    int lca_level = 0;
    for (int i = x, j = y;
         (lca_level = level[i]) &&
         i != j;
         level[i] < level[j] ? (j = par[j]) : (i = par[i]))
        ;

    return dist[lca_level][x] + dist[lca_level][y];
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        scanf("%d %d %d", U + i, V + i, W + i);
        g[U[i]].push_back(i), g[V[i]].push_back(i);
    }
    decompose(1);
    int m;
    scanf("%d", &m);
    while (m--)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", compute_distance(x, y));
    }
}