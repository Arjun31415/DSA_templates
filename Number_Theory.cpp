#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

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

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
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
//Calculation of (x^y)%mm

long long binpow(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
long long binpow(long long a, long long b, long long m)
{
    a %= m;
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
// Call FIO in main
signed main()
{

    return 0;
}