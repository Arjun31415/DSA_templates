#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

// Range updates and point queries;
// to update a range [a,b] with +x; do update(a,x) and update(1+b,-x);
// to query a range [0,a] do ft.query(a+1);

template <typename T>
struct FT
{
    vector<T> s;
    FT(long long n) : s(n) {}
    void update(unsigned long long pos, T dif)
    {
        // a[pos] += dif
        for (; pos < sz(s); pos |= pos + 1)
            s[pos] += dif;
    }
    void update(unsigned long long a, unsigned long long b, T x)
    {
        update(a, x), update(1 + b, -x);
        return;
    }
    // returns sum of values in [0, pos)
    T query(unsigned long long pos)
    {

        ll res = 0;
        for (; pos > 0; pos &= pos - 1)
            res += s[pos - 1];
        return res;
    }
    //  query [l,r];
    T query(unsigned long long l, unsigned long long r)
    {
        return query(r + 1) - query(l);
    }

    T lower_bound(T sum)
    { // min pos s t sum of [0 , pos ] >= sum
        // Returns n i f no sum is >= sum, or −1 i f empty sum is .
        if (sum <= 0)
            return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1)
        {
            if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
                pos += pw, sum -= s[pos - 1];
        }
        return pos;
    }
};
