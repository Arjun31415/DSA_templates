/* 
    Segment tree supporting point updates and range queries 
   currently supports range max query 
   TODO: range sum queries
   current lazy update is set a[i]+=val;
   version 2 will have
   set a[i]=x;
*/

#include <bits\stdc++.h>
using namespace std;

#define vi vector<int>
#define lc(x) (x << 1)
#define rc(x) ((x << 1) | 1)
#define pb push_back

#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Data
{
    //Use required attributes
    int mn = 0;

    //Default Values
    Data() : mn(0){};
};

struct SegTree
{
    int N;
    vector<Data> st;
    vector<bool> cLazy;
    vector<int> lazy;
    vector<int> a;

    void init(int n)
    {
        N = n;
        st.resize(4 * N + 5);
        cLazy.assign(4 * N + 5, false);
        lazy.assign(4 * N + 5, 0);
    }
    void init(int n, vi a)
    {
        init(n);
        this->a = move(a);
        build(1, 1, N);
    }

    //Write required merge functions
    void merge(Data &cur, Data &l, Data &r)
    {
        cur.mn = max(l.mn, r.mn);
    }

    //Handle lazy propagation appriopriately
    void propagate(int node, int L, int R)
    {
        if (lazy[node] == 0)
            return;
        st[node].mn += lazy[node];
        if (L != R)
        {
            cLazy[node * 2] = 1;
            cLazy[node * 2 + 1] = 1;
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        cLazy[node] = 0;
        lazy[node] = 0;
    }

    void build(int node, int L, int R)
    {
        if (L == R)
        {
            st[node].mn = 0;
            return;
        }
        int M = L + (R - L) / 2;
        build(node * 2, L, M);
        build(node * 2 + 1, M + 1, R);
        merge(st[node], st[node * 2], st[node * 2 + 1]);
    }

    Data Query(int node, int L, int R, int i, int j)
    {
        if (cLazy[node])
            propagate(node, L, R);
        if (j < L || i > R)
            return Data();
        if (i <= L && R <= j)
            return st[node];
        int M = (L + R) / 2;
        Data left = Query(node * 2, L, M, i, j);
        Data right = Query(node * 2 + 1, M + 1, R, i, j);
        Data cur;
        merge(cur, left, right);
        return cur;
    }

    Data pQuery(int node, int L, int R, int pos)
    {
        if (cLazy[node])
            propagate(node, L, R);
        if (L == R)
            return st[node];
        int M = L + (R - L) / 2;
        if (pos <= M)
            return pQuery(node * 2, L, M, pos);
        else
            return pQuery(node * 2 + 1, M + 1, R, pos);
    }

    void Update(int node, int L, int R, int i, int j, int val)
    {
        if (cLazy[node])
            propagate(node, L, R);
        if (j < L || i > R)
            return;
        if (i <= L && R <= j)
        {
            cLazy[node] = 1;
            lazy[node] += val;
            propagate(node, L, R);
            return;
        }
        int M = L + (R - L) / 2;
        Update(node * 2, L, M, i, j, val);
        Update(node * 2 + 1, M + 1, R, i, j, val);
        merge(st[node], st[node * 2], st[node * 2 + 1]);
    }

    void pUpdate(int node, int L, int R, int pos, int val)
    {
        if (cLazy[node])
            propagate(node, L, R);
        if (L == R)
        {
            cLazy[node] = 1;
            lazy[node] = val;
            propagate(node, L, R);
            return;
        }
        int M = L + (R - L) / 2;
        if (pos <= M)
            pUpdate(node * 2, L, M, pos, val);
        else
            pUpdate(node * 2 + 1, M + 1, R, pos, val);
        merge(st[node], st[node * 2], st[node * 2 + 1]);
    }

    Data query(int pos)
    {
        return pQuery(1, 1, N, pos);
    }

    Data query(int l, int r)
    {
        return Query(1, 1, N, l, r);
    }

    void update(int pos, int val)
    {
        pUpdate(1, 1, N, pos, val);
    }

    void update(int l, int r, int val)
    {
        Update(1, 1, N, l, r, val);
    }
} ST;