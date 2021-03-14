/* 
    Segment tree supporting point updates and range queries 
    source array (a) is 0 indexed 
    segment tree (t) is 1 indexed 
    call modify function for range updates.
    modify fuunction also supports point updates by giving range as[l,l] 
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
struct SegmentTree
{
    int n;
    vector<int> a, t, lazy;

    void init(int x)
    {
        n = x;
        t.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void init(int x, vector<int> y)
    {
        n = x;
        a = y;
        t.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int merge(int x, int y) { return x + y; }

    int upd(int x, int y) { return x + y; }

    void build(int i, int l, int r)
    {
        if (l == r)
        {
            t[i] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(lc(i), l, mid);
        build(rc(i), mid + 1, r);
        t[i] = merge(t[lc(i)], t[rc(i)]);
    }

    void push(int i, int l, int r) // i-> tree index , l-> left bound, r-> right bound for range updates
    {
        t[i] = upd(t[i], (lazy[i] * (r - l + 1)));
        if (l != r)
        {
            lazy[lc(i)] = upd(lazy[lc(i)], lazy[i]);
            lazy[rc(i)] = upd(lazy[rc(i)], lazy[i]);
        }
        lazy[i] = 0;
    }
    // call modify not push
    void modify(int i, int l, int r, int ql, int qr, int val)
    {
        if (l > qr || r < ql)
            return;
        if (lazy[i] != 0)
            push(i, l, r);
        if (l >= ql && r <= qr)
        {
            lazy[i] = upd(lazy[i], val);
            push(i, l, r);
            return;
        }
        int mid = (l + r) / 2;
        modify(lc(i), l, mid, ql, qr, val);
        modify(rc(i), mid + 1, r, ql, qr, val);
        t[i] = merge(t[lc(i)], t[rc(i)]);
    }

    int query(int i, int l, int r, int ql, int qr)
    {
        if (l > qr || r < ql)
            return 0;
        if (lazy[i] != 0)
            push(i, l, r);
        if (l >= ql && r <= qr)
            return t[i];
        int mid = (l + r) / 2;
        int resL = query(lc(i), l, mid, ql, qr);
        int resR = query(rc(i), mid + 1, r, ql, qr);
        return merge(resL, resR);
    }

    void modify(int l, int r, int val) { modify(1, 0, n - 1, l, r, val); }

    void modify(int pos, int val) { modify(1, 0, n - 1, pos, pos, val); }

    int query(int l, int r) { return query(1, 0, n - 1, l, r); }

    int query(int pos) { return query(1, 0, n - 1, pos, pos); }
};