#include <bits/stdc++.h>
#define int long long
using namespace std;
#define pb push_back
#define pii pair<int, int>
#define vi vector<int>
#define ff first
#define ss second

class union_find
{
    int n;
    vector<int> par;
    vector<int> sz;

public:
    // constructor to intialize the par and sz;
    union_find(int nval)
    {
        n = nval;
        par.resize(n + 1);
        sz.resize(n + 1);

        for (int i = 1; i <= n; ++i)
            par[i] = i, sz[i] = 1;
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

    //O(1) ammortized
    int root(int a)
    {
        // if (x == par[x])
        //     return x;

        // return par[x] = root(par[x]);
        return (par[a] = (par[a] == a ? a : root(par[a])));
    }

    //O(1) ammortized
    bool find(int a, int b)
    {
        return root(a) == root(b);
    }

    //O(1) ammortized
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
signed main()
{
    int n;
    cin >> n;
    int d = (n * (n - 1)) / 2;

    vector<pii> stop(d);

    for (pii &x : stop)
        cin >> x.ff >> x.ss;

    vi ans;

    int num = n;
    union_find dsu(n);

    for (int i = d - 1; i >= 0; --i)
    {
        num -= dsu.un(stop[i].ff, stop[i].ss);

        ans.pb(num);
    }

    reverse(ans.begin(), ans.end());

    for (int comp : ans)
        cout << comp << '\n';
    return 0;
}