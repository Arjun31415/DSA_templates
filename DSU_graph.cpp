/*
    Given N nodes numbered from 1 to N
    there are Q queries of the form (u,v,g).
    For every pair of nodes (i,j) there exists a path between i and j iff gcd(i,j)>=g.
    Find out whether a path exists between (u,v).,i.e whether u,v lie in the same connected component
    Print "YES" if the path exist else print "NO" 
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <type_traits>
using namespace __gnu_pbds;
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
#define sign(x) (x > 0) - (x < 0)
#define is_poweroftwo(n) (n && !(n & (n - 1)))
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
template <typename T>
#define ordered_set(T) = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void nothing();
void tracearr(vi a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cerr << i << "th index " << a[i] << endl;
    }
    cerr << endl;
}

void tracearr(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cerr << i << "th index " << a[i] << endl;
    }
    cerr << endl;
}
void trace2d(vector<vi> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            cerr << a[i][j] << " ";
        }
        cerr << endl;
    }
}
void print(vi a, int l, int u)
{
    for (int i = 0; i < u; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";
}
void print(vi a)
{

    print(a, 0, a.size());
}
void printl(vi a, int l)
{
    print(a, l, a.size());
}
void printu(vi a, int u)
{
    print(a, 0, u);
}
class union_find
{
    int n;
    vector<int> par;
    vector<int> sz;

public:
    union_find(int nval)
    {
        n = nval;
        par.resize(n + 1);
        sz.resize(n + 1);

        for (int i = 1; i <= n; ++i)
            par[i] = i,
            sz[i] = 1;
    }
    union_find(vector<int> &p)
    {
        par = p;
        n = par.size() + 1;
    }
    union_find(vector<int> &p, vector<int> &r)
    {
        par = p;
        n = par.size() + 1;
        sz = r;
    }
    int root(int a)
    {
        return (par[a] = (par[a] == a ? a : root(par[a])));
    }
    bool find(int a, int b)
    {
        return root(a) == root(b);
    }
    int un(int a, int b)
    {
        int ra = root(a);
        int rb = root(b);

        if (ra == rb)
            return 0;

        if (sz[ra] > sz[rb])
            swap(ra, rb);

        par[ra] = rb;
        sz[rb] += sz[ra];
        return 1;
    }
    // 1 based indexing by default
};
struct query
{
    int u, v, g, id;
    bool ans;
    query(int u, int v, int g, int i)
    {
        this->u = u;
        this->v = v;
        this->g = g;
        this->id = i;
    }
    bool inline operator<(const query &other)
    {
        return this->g < other.g;
    }
};
// Call FIO in main
void calc(query q, int prev, int n, union_find &DSU)
{
    for (int i = q.g; i < prev; i++)
    {
        for (int j = i; j + i <= n; j += i)
        {
            DSU.un(j, j + i);
        }
    }
}
int32_t main()
{
    FIO;
    int n, Q;
    cin >> n >> Q;
    union_find DSU(n);
    vector<query> q;
    vi ans(Q);
    for (int i = 0; i < Q; i++)
    {
        int u, v, g;
        cin >> u >> v >> g;
        q.pb(query(u, v, g, i));
    }
    sort(q.rbegin(), q.rend());
    int prev = n + 1;
    for (int i = 0; i < Q; i++)
    {
        calc(q[i], prev, n, DSU);
        q[i].ans = ans[q[i].id] = DSU.find(q[i].u, q[i].v);
    }
    for (int i = 0; i < Q; i++)
    {
        cout << (ans[i] == 1 ? "YES\n" : "NO\n");
    }

    return 0;
}