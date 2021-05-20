#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

// Range updates and point queries;
// to update a range [a,b] with +x; do update(a,x) and update(1+b,-x);
// to query a range [0,a] do ft.query(a+1);
struct FT
{
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif)
    {
        // a[pos] += dif
        for (; pos < sz(s); pos |= pos + 1)
            s[pos] += dif;
    }
    // returns sum of values in [0, pos)
    ll query(int pos)
    {

        ll res = 0;
        for (; pos > 0; pos &= pos - 1)
            res += s[pos - 1];
        return res;
    }
};