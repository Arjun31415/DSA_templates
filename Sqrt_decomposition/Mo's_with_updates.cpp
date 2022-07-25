// Tanuj Khattar
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
const int Q = 1e5 + 10;
int A[N], last[N], rev[N + Q], cnt[N + Q];
bool use[N];
struct Query
{
    int idx, l, r, t, lb, rb;
} q[Q];
struct Update
{
    int x, new_y, prv_y;
} u[Q];
int nq, nu, compressed_val;
int64_t ans[Q], curr_ans;
void process_element(int x, bool add = true)
{
    use[x] = add;
    if (add && ++cnt[A[x]] == 1)
    {
        curr_ans += rev[A[x]];
    }
    else if (!add && --cnt[A[x]] == 0)
    {
        curr_ans -= rev[A[x]];
    }
}
void reflect_update(int i, bool forward = true)
{
    int x = u[i].x;
    int y = forward ? u[i].new_y : u[i].prv_y;
    if (!use[x])
    {
        A[x] = y;
        return;
    }
    process_element(x, false);
    A[x] = y;
    process_element(x, true);
}
bool cmp(Query a, Query b)
{
    return (a.lb < b.lb) || (a.lb == b.lb && a.rb < b.rb) ||
           (a.lb == b.lb && a.rb == b.rb && a.t < b.t);
}
int main()
{
    // Read Input.
    int n;
    scanf("%d", &n);
    int block = pow(n, 2.0 / 3.0);
    map<int, int> mp;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", A + i);
        last[i] = A[i];
        mp[A[i]];
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        char s[2];
        int x, y;
        scanf("%s %d %d", s, &x, &y);
        if (s[0] == 'Q')
        {
            nq++;
            q[nq] = {nq, x, y, nu, x / block, y / block};
        }
        else
        {
            u[++nu] = {x, y, last[x]};
            last[x] = y;
            mp[y];
        }
    }
    // Coordinate compression.
    for (auto &it : mp)
    {
        it.second = ++compressed_val;
        rev[compressed_val] = it.first;
    }
    for (int i = 1; i <= n; i++)
    {
        A[i] = mp[A[i]];
    }
    for (int i = 1; i <= nu; i++)
    {
        u[i].new_y = mp[u[i].new_y];
        u[i].prv_y = mp[u[i].prv_y];
    }
    // Sort the queries.
    sort(q + 1, q + nq + 1, cmp);
    // Answer the queries.
    for (int i = 1, T = 0, L = 1, R = 0; i <= nq; i++)
    {
        while (T < q[i].t)
            reflect_update(++T, true);
        while (T > q[i].t)
            reflect_update(T--, false);
        while (R < q[i].r)
            process_element(++R, true);
        while (L > q[i].l)
            process_element(--L, true);
        while (R > q[i].r)
            process_element(R--, false);
        while (L < q[i].l)
            process_element(L++, false);
        ans[q[i].idx] = curr_ans;
    }
    for (int i = 1; i <= nq; i++)
    {
        printf("%lld\n", ans[i]);
    }
}