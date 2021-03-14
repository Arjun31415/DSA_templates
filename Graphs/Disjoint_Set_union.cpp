#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define FOR(i, a, b, c) for (ll i = a; i < b; i += c)
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
#define epsilon 1e-9
#define sign(x) (x > 0) - (x < 0)
#define is_poweroftwo(n) (n && !(n & (n - 1)))
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

// takes in a parent array and
// an element a and
//finds the parent of the given element
ll get(vi &parent, int a)
{

    return (parent[a] = (parent[a] == a ? a : get(parent, parent[a])));
}
// takes in a parent array
// a rank array denoting the rank of each group
// two elements who need to be merged together
int Union(vi &parent, vi &rank, int a, int b)
{
    a = get(parent, a);
    b = get(parent, b);
    // if they are already merged then do nothing
    if (a == b)
    {
        return 1;
    }
    if (rank[a] == rank[b])
    {
        // if they have the same rank then they have gone thorugh the same number of merges
        // so make any one bigger, it does not matter
        rank[a]++;
    }
    if (rank[a] > rank[b])
    {
        // merge b into a
        parent[b] = a;
    }
    else
    {
        parent[a] = b;
    }
    return 0;
}

void tracearr(vi a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cerr << i << "th index " << a[i] << endl;
    }
    cerr << endl;
}

// edges is the adjacency edge list
// n is the number of vertices in the graph
int find_cycles(vector<vi> edges, int n)
{
    vi parent(n + 1);
    vi rank(n + 1, 0);

    for (auto e : edges)
    {

        parent[e[0]] = e[0];
        parent[e[1]] = e[1];
    }

    for (auto e : edges)
    {
        // e[0],e[1]are vertices and e[2] is weight of the edge

        int x = Union(parent, rank, e[0], e[1]);
        //tracearr(parent);
        if (x == 1)
        {
            cout << "Yes\n";
            return 1;
        }
    }

    cout << "No\n";
    return 0;
}
int32_t main()
{
    int n, m;
    cin >> n >> m;
    // vi parent(n + 1);
    // vi rank(n + 1, 0);
    // //  n number of elements
    // // m number of queries
    // for (int i = 0; i < n; i++)
    // {
    //     parent[i] = i;
    // }
    // while (m--)
    // {
    //     string str;
    //     cin >> str;
    //     if (str == "union")
    //     {
    //         int x, y;
    //         cin >> x >> y;
    //         Union(parent, rank, x, y);
    //     }
    //     else
    //     {
    //         int x;
    //         cin >> x;
    //         cout << get(parent, x);
    //     }
    // }
    vector<vi> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.pb({u, v, w});
    }
    int x = find_cycles(edges, n);
    //cout<<x<<endl;
}