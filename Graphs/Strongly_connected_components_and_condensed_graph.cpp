#include <bits/stdc++.h>
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
#define mod 1000000007
#define inf 1e18
#define w(x)  \
    int x;    \
    cin >> x; \
    while (x--)
#define trace(x) cerr << #x << ": " << x << " " << endl;

int n, m;                    // number of nodes and number of edges reespectively
vector<vi> adj, rev, cg_adj; // condensed graph
vi scc_no;                   //strongly connected component number

void dfs(int i, vi &vis, vi &vals)
{
    vis[i] = 1;

    for (int j : adj[i])
        if (!vis[j])
            dfs(j, vis, vals);

    vals.pb(i); //nodes in increasing order of out time
}

void rev_dfs(int i, int num)
{
    // the ith node is in the C (num) connected component
    scc_no[i] = num;

    for (int j : rev[i])
    {
        if (!scc_no[j])
            rev_dfs(j, num);
    }
}

int condensation_graph()
{
    vi vis(n + 1), vals;

    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            dfs(i, vis, vals);

    reverse(vals.begin(), vals.end());

    // number of strongly connected components
    int num = 1;

    scc_no.assign(n + 1, 0);

    for (int i : vals)
    {
        if (!scc_no[i])
        {
            rev_dfs(i, num);
            /* all nodes which are visitable from i
            in the reverse graph are part of the 
            same strongly connected component as i
            */
            num++;
        }
    }

    cg_adj.resize(num); //num = no_of_sccs + 1

    for (int i = 1; i <= n; ++i)
        for (int j : adj[i])
            if (scc_no[i] != scc_no[j])
                cg_adj[scc_no[i]].pb(scc_no[j]);

    return num - 1; // return number of strongly connected components
}

int32_t main()
{

    cin >> n >> m;
    adj.resize(n + 1), rev.resize(n + 1);

    while (m--)
    {
        int i, j;
        cin >> i >> j;
        adj[i].pb(j);
        rev[j].pb(i);
    }

    int sccs = condensation_graph();

    for (int i = 1; i <= n; ++i)
        cout << i << ' ' << scc_no[i] << '\n';
    cout << '\n';

    for (int i = 1; i <= sccs; ++i)
        for (int j : cg_adj[i])
            cout << i << ' ' << j << '\n';

    return 0;
}
