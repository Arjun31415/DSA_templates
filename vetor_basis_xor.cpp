
//Given a set S of size 1≤n≤10^5
//with elements 0≤ai<2^20.
// Find the number of distinct integers
//that can be represented using xor over the set of the given elements.
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define lc(x) (x << 1)
#define rc(x) ((x << 1) | 1)
#define pb push_back
// 0 based segment tree
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);                  \
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
string s;
long N;
class xorbasis
{
public:
    vector<int> basis;

    // size of basis
    unsigned long long sz;
    
    // number of dimensions,here number of bits and length of bitmask
    unsigned long long d;

    xorbasis(unsigned long long _d)
    {
        d = _d;
        basis = move(vector<int>(d, 0));
        sz = 0;
    }
    void insertVector(int mask)
    {
        for (int i = 0; i < d; i++)
        {
            if ((mask & 1 << i) == 0)
                continue; // continue if i != f(mask)

            if (!basis.at(i))
            { // If there is no basis vector with the i'th bit set, then insert this vector into the basis
                basis.at(i) = mask;
                ++sz;

                return;
            }

            mask ^= basis.at(i); // Otherwise subtract the basis vector from this vector
        }
    }
};
int main()
{
    int T;
    cin >> T;
    int32_t n, q;
    while (T--)
    {

        cin >> q >> n;
        int32_t a;
        xorbasis X(20);
        for (int i = 0; i < n; ++i)
        {
            cin >> a;
            X.insertVector(a);
        }
        cout << (1 << q) / (1 << X.sz) << "\n";
    }

    //Think of each element as a vector of dimension d=20.
    // Then the vector space is Z^(20) 2(subscript).
    // We can find it's basis in O(d⋅n).
    // For any linear combination of the basis vectors,
    // we get a different possible xor of some subset.
    // So, the answer would be 2^(size of basis).
    // It would fit in an integer type,
    //since size of basis ≤d=20 by property 7.

    return 0;
}