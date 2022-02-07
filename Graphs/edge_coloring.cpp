#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

using vi = vector<int>;
vector<vector<pii>> adj;
vector<int> color;

/**
 * @brief edge coloring using minimum number of colors
 *
 * @param n number of vertices
 * @param adj adj[i] => {adjacent vertex,edge number}
 * @param root starting vertex
 * @return int minimum number of colors
 */
int color_tree(int n, vector<vector<pii>> &adj, int root = 1)
{

    // To store the minimum colors
    int K = 0;
    // Color of edge between its parent
    vector<int> cs(n + 1, 0);
    vector<int> vis(n + 1, 0);
    queue<int> que;
    vis[1] = 1;
    que.push(root);
    while (!que.empty())
    {

        // Take first element of the queue
        int v = que.front();
        que.pop();

        // Take the possible value of K
        if (K < (int)adj[v].size())
            K = adj[v].size();
        // Current color
        int cur = 1;
        for (auto [u, e] : adj[v])
        {
            if (vis[u])
                continue;
            if (cur == cs[v])
                cur++;
            cs[u] = color[e] = cur++;
            vis[u] = 1;
            que.push(u);
        }
    }
    if (K > 2)
        cout << "-1\n";
    else
        for (int i = 1; i < n; i++)
            cout << (color[i] == 1 ? "2 " : "17 ");
    return 0;
}