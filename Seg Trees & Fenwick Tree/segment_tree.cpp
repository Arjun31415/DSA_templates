/* 
    Segment tree supporting point updates and range queries 
    source array (a) is 0 indexed 
    segment tree (t) is 1 indexed 
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define lc(x) (x << 1)
#define rc(x) ((x << 1) | 1)
#define pb push_back
// 0 based segment tree
// the query range is also 0 based indexing
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
string s;
long N;
struct SegmentTree
{
    long n; // size of source array a
    // t is the segment tree
    vector<int> a, t;

    void init(int x)
    {
        n = x;
        t.assign(4 * n, 0);
    }

    void init(long x, vector<int> y)
    {
        n = x;
        a = move(y);
        t.resize(4 * n);
        build(1, 0, n - 1);
    }

    long merge(long x, long y) { return x + y; }

    long upd(long x, long y) { return y; }

    void build(int i, long l, long r)
    {

        if (l == r)
        {
            t[i] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc(i), l, mid);
        build(rc(i), mid + 1, r);
        t[i] = merge(t[lc(i)], t[rc(i)]);
    }

    void modify(int i, long l, long r, long pos, long val) //point update
    {
        if (l == r)
        {
            t[i] = upd(t[i], val);
            return;
        }
        long mid = (l + r) >> 1;
        if (pos <= mid)
            modify(lc(i), l, mid, pos, val);
        else
            modify(rc(i), mid + 1, r, pos, val);
        t[i] = merge(t[lc(i)], t[rc(i)]);
    }

    // query in the range [ql,qr] both inclusive

    long query(int i, long l, long r, long ql, long qr)
    {
        if (l > qr || r < ql)
            return 0;
        if (l >= ql && r <= qr)
            return t[i];
        int mid = (l + r) >> 1;
        return merge(query(lc(i), l, mid, ql, qr), query(rc(i), mid + 1, r, ql, qr));
    }

    void modify(long pos, long val) { modify(1, 0, n - 1, pos, val); }

    long query(long l, long r) { return query(1, 0, n - 1, l, r); }
} ST;