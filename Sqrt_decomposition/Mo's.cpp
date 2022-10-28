#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

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

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
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
// Call FIO in main
class Query
{
public:
    int L, r, lb, rb, B;
    int order;
    Query(int L, int R, int B, int i)
    {
        this->L = L;
        this->r = R;
        this->lb = L / B;
        this->rb = R / B;
        this->order = i;
    }
    Query(int L, int R, int B)
    {
        this->L = L;
        this->r = R;
        this->lb = L / B;
        this->rb = R / B;
    }
    Query(int L, int R)
    {
        this->L = L;
        this->r = R;
    }
};
inline bool operator<(const Query &a, const Query &b)
{
    return (a.lb < b.lb) || (a.lb == b.lb && a.lb & 1 ? a.r < b.r : a.r > b.r);
}
signed main()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    FIO;
    int T; // number of test cases
    cin >> T;

    /*Enter code here */
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    cerr << duration;
    return 0;
}