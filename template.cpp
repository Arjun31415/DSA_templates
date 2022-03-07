#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

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
#define sz(x) (int)(x).size()
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

#define debugging
#ifdef debugging
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

template <typename T>
void print(vector<T> a, int l, int u, string separator = " ")
{
    for (int i = l; i < u; i++)
    {
        cout << a[i] << separator;
    }
    cout << "\n";
}
template <typename T>
void print(vector<T> a, string separator = " ")
{

    print(a, 0, a.size(), separator);
}
template <typename T>
void printl(vector<T> a, int l, string separator = " ")
{
    print(a, l, a.size(), separator);
}
template <typename T>
void printu(vector<T> a, int u, string separator = " ")
{
    print(a, 0, u, separator);
}
template <typename T1, typename T2>
void print(pair<T1, T2> a)
{
    cout << "{" << a.ff << ", " << a.ss << "}";
}
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
// Miller-Rabin Primality test
bool isprime(ll n)
{
    if (n < 2)
        return false;
    for (ll x : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if (n == x)
            return true;
        bool flag = true;
        ll r = 1;
        ll t = 1;
        while (r <= ((n - 1) >> __builtin_ctzll(n - 1)))
        {
            if (r & ((n - 1) >> __builtin_ctzll(n - 1)))
                t = ((__int128)t * x) % n;
            x = ((__int128)x * x) % n;
            r <<= 1;
        }
        if (t == 1 || t == n - 1)
            flag = false;
        for (r = 0; r < __builtin_ctzll(n - 1); r++)
        {
            t = ((__int128)t * t) % n;
            if (t == n - 1)
                flag = false;
        }
        if (flag)
            return false;
    }
    return true;
}
// overflow error is possible
int leftbit(long long n)
{

    (((((n |= n >> 1) |= n >> 2) |= n >> 4) |= n >> 8) |= n >> 16);
    // n |= n >> 1;
    //  n |= n >> 2;
    //  n |= n >> 4;
    //  n |= n >> 8;
    //  n |= n >> 16;
    n = n + 1;
    // return the nearest power of 2
    // return (n >> 1);
    // return the left bit
    return (log2(n >> 1));
}
// ultall takes a number and toggles all bits till the Most significant bit (MSB)
// and return this number
int ultall(unsigned long long n)
{

    int max = leftbit(n);
    for (int i = 0; i <= max; i++)
    {
        n ^= (1 << i);
    }
    return n;
}
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
signed main()
{
#ifndef ONLINE_JUDGE
#ifndef CPH
    auto t1 = std::chrono::high_resolution_clock::now();
#endif
#endif
    FIO;
    w(T)
    {
        calc();
    }

#ifndef ONLINE_JUDGE
#ifndef CPH
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    cerr << duration;
#endif
#endif
    return 0;
}