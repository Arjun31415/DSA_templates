/*
                         Square Root Decomposition on Array

    query         :given [L,R,K] return number of elements >K in [L,R]
    point uypdate : given i,val set A[i]=val

    Time : O(N*log(N)*sqrt(N))

Note:
    1) Another method is by maintaining Merge sort tree
    2) Maintaining persistent segment tree and apply square root decomposition
on the queries. This method(using Persistent Segment Trees) is better because it
has smaller constant factor
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
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
#define w(x)                                                                   \
    int x;                                                                     \
    cin >> x;                                                                  \
    while (x--)
#define trace(x) cerr << #x << ": " << x << " " << endl;
#define FIO                                                                    \
    ios_base::sync_with_stdio(0);                                              \
    cin.tie(0);                                                                \
    cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define epsilon 1e-9
#define sign(x) (x > 0) - (x < 0)
#define is_poweroftwo(n) (n && !(n & (n - 1)))
typedef long long ll;

typedef unsigned long long ull;

typedef long double ld;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    pbds;
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
void print(vi a) { print(a, 0, a.size()); }
void printl(vi a, int l) { print(a, l, a.size()); }
void printu(vi a, int u) { print(a, 0, u); }
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
signed main()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    FIO;
    int N;
    cin >> N;
    int B = 2 * sqrt(N);
    vi a(N, 0);
    vector<vi> S(N / B + 1);

    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        S[i / B].pb(a[i]);
        // trace(S[i / B][i % B]);
    }
    for (int i = 0; i < N / B; i++)
    {
        sort(all(S[i]));
    }
    // trace2d(S);
    int q;
    cin >> q;
    while (q--)
    {
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            int L, R, K;
            cin >> L >> R >> K;
            L--;
            R--;

            // step 1:
            int ans = 0;

            int bl = L / B;
            int end = bl * B + B - 1;

            int br = R / B;
            int begin = br * B;
            if (bl == br)
            {
                for (int i = L; i <= R; i++)
                {
                    if (a[i] > K)
                        ans++;
                }
                cout << ans << "\n";
                continue;
            }
            // trace(bl);
            // trace(end);

            for (int i = L; i <= end; i++)
            {
                // trace(a[i]);
                if (a[i] > K)
                    ans++;
            }
            // step 2:

            for (int i = begin; i <= R; i++)
            {
                // trace(a[i]);
                if (a[i] > K)
                    ans++;
            }

            // step 3:
            for (int b = bl + 1; b < br; b++)
            {
                int x = upper_bound(all(S[b]), K) - S[b].begin();
                ans += B - 1 - x + 1;
            }

            cout << ans << "\n";
        }
        else
        {
            int pos, val;
            cin >> pos >> val;
            a[--pos] = val;
            int b = pos / B;
            int i = pos % B;
            S[b][i] = val;
            sort(all(S[b]));
            // cerr << "\n\n";
            // trace2d(S);
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    // cerr << duration << " us";
    return 0;
}
