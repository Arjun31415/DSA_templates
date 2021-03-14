
#include <bits/stdc++.h>
using namespace std;
// String Hashing with only one mod

const int N = 1e6 + 6;
const int mod = 1e9 + 7;
const int base = 33;

int add(int a, int b, int mod)
{
    int res = (a + b) % mod;
    if (res < 0)
        res += mod;
    return res;
}

int mult(int a, int b, int mod)
{
    int res = (a * 1LL * b) % mod;
    if (res < 0)
        res += mod;
    return res;
}

int power(int a, int b, int mod)
{
    int res = 1;
    while (b)
    {
        if ((b % 2) == 1)
            res = mult(res, a, mod);
        a = mult(a, a, mod);
        b /= 2;
    }
    return res;
}

int pw[N];
int inv[N];
int H[N];

void precalc()
{
    pw[0] = 1;
    for (int i = 1; i < N; i++)
        pw[i] = mult(pw[i - 1], base, mod);

    int pw_inv = power(base, mod - 2, mod);
    inv[0] = 1;
    for (int i = 1; i < N; i++)
        inv[i] = mult(inv[i - 1], pw_inv, mod);
}

void build(string s)
{
    int n = s.length();
    for (int i = 0; i < n; ++i)
    {
        H[i] = add((i == 0) ? 0 : H[i - 1], mult(pw[i], s[i] - 'a' + 1, mod), mod);
    }
}

// get the hash of a substring from (x,y]
int getHash(int x, int y)
{
    int res = add(H[y], (x == 0) ? 0 : -H[x - 1], mod);
    res = mult(res, (x == 0) ? 1 : inv[x], mod);
    return res;
}

/*
Example and how to use 
int main() {
    precalc();
    string s = "ABCDEFGABCDEFGH";
    build(s);
    cout<< getHash(2, 5) << " == " << getHash(9, 12) << endl;
}*/