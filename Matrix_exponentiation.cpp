#include <bits/stdc++.h>
using namespace std;
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define mod 1000000007
#define inf 1e18
#define vi vector<int>
typedef long long ll;
// p1 is the answer matrix
// n is the order of the identity matrix
void Miden(ll **p1, ll n)
{
    ll(*x)[n] = (ll(*)[n])p1;
    REP(i, 0, n)
    {
        REP(j, 0, n)
        {
            x[i][j] = 0;
        }
        x[i][i] = 1;
    }
    return;
}
// p1 is the first matrix
// p2 is the second matrix
// ans is the output matrix
//x is number of rows in p1
//y is number of columns in p1
//z is number of columns in p2
//m is the mod
void Mmult(ll **p1, ll **p2, ll **ans, ll x, ll y, ll z, ll m = mod)
{
    ll(*a)[y] = (ll(*)[y])p1;
    ll(*b)[z] = (ll(*)[z])p2;
    ll(*c)[z] = (ll(*)[z])ans;
    REP(i, 0, x)
    {
        REP(j, 0, z)
        {
            c[i][j] = 0;
            REP(k, 0, y)
            {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= m;
            }
        }
    }
    return;
}
// p1 is the input matrix
//ans is the matrix in which the answer is to be stored
//n is the order of the square matrix p1
// y is the power given
// m is the mod

void Mpow(ll **p1, ll **ans, ll n, ll y, ll m = mod)
{
    if (y == 0)
    {
        Miden(ans, n);
        return;
    }
    ll t[n][n];
    Mpow(p1, (ll **)t, n, y / 2, m);
    ll z[n][n];
    Mmult((ll **)t, (ll **)t, (ll **)z, n, n, n, m);
    if (y % 2)
    {
        Mmult((ll **)z, p1, ans, n, n, n, m);
    }
    else
    {
        Miden((ll **)t, n);
        Mmult((ll **)z, (ll **)t, ans, n, n, n, m);
    }
    return;
}

// Call FIO in main
signed main()
{
    //FIO;
    ll n;
    cin >> n;
    auto t1 = std::chrono::high_resolution_clock::now();
    ll mat[2][2] = {
        {1, 1}, {1, 0}};
    ll ans[2][2];
    Mpow((ll **)mat, (ll **)ans, 2, n, mod);
    cout << ((ans[1][0] * 1 + ans[1][1] * 1) % mod);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cerr << "\n"
              << duration;

    return 0;
}
