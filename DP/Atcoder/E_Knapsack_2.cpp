/**
 * @file E_Knapsack_2.cpp
 * @author Arjun
 * @brief solutuion to https://atcoder.jp/contests/dp/tasks/dp_e
 * @version 0.1
 * @date 2022-02-02
 *
 *
 * Notice that value is small (at most 1e5 for all 100 items), so instead of "what is the most value we can carry with weight W", you find "what is the least weight you need to carry to get a value of V".

 */
#include <bits/stdc++.h>

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
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p)
{
    os << '{' << p.first << ", " << p.second << '}';
    return os;
}

template <typename C,
          typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
          typename std::enable_if<!std::is_same<C, std::string>::value>::type * = nullptr>
ostream &operator<<(ostream &os, const C &container)
{
    bool first = true;
    stringstream ss;
    ss << '[';
    for (const auto &x : container)
    {
        if (!first)
        {
            ss << ", ";
        }
        first = false;
        ss << x;
    }
    ss << ']';
    return os << ss.str();
}

#ifndef debugging
#define debug(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char *name, Arg1 &&arg1)
{
    cerr << name << " : " << arg1 << '\n';
}
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&...args)
{
    const char *comma = strchr(names + 1, ',');
    cerr.write(names, comma - names) << " : " << arg1 << " | ";
    __f(comma + 1, args...);
}
#else
#define debug(...) ;
#endif

int calc(const vi &w, const vi &v, const int &n, const int &m)
{
    const int N = 1e2;
    vi dp(N + 1, inf), tp(N + 1, inf);
    dp[0] = 0;
    tp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (j - v[i] >= 0)
                dp[j] = min(dp[j], tp[j - v[i]] + w[i]);
        }
        tp = dp;
    }
    for (int i = N; i >= 0; i--)
    {
        if (dp[i] <= m)
            return i;
    }
    return dp[1];
}
signed main()
{
    FIO;
    int n, m;
    cin >> n >> m;
    vi w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> v[i];
    cout << calc(w, v, n, m);
    return 0;
}